#include <QGraphicsPixmapItem>

#include "CustomButton.h"

QRectF Shadow::boundingRectFor(const QRectF& rect) const
{
	return rect.united(rect.translated(0, 0).adjusted(-blurRadius - distance, -blurRadius - distance, blurRadius + distance, blurRadius + distance));
}

void Shadow::draw(QPainter* painter)
{
	PixmapPadMode mode = PadToEffectiveBoundingRect;//����ӳ��ģʽ
	QPoint pos;
	const QPixmap px = sourcePixmap(Qt::DeviceCoordinates, &pos, mode);//��ȡԴͼ��
	//Qt::DeviceCoordinates��һ��ö��ֵ����ʾ����ϵͳΪ�豸���ꡣ��Qt�У����ڲ�ͬ������ϵͳ���豸��������������ʾ�豸��ص����꣬ͨ��������Ϊ��λ��
	if(px.isNull())//�ж�ͼ���Ƿ�Ϊ��
		return;
	QTransform restoreTransform = painter->worldTransform();//���浱ǰ���ҵ�����任
	painter->setWorldTransform(QTransform());//������任����Ϊ��
	if(px.isNull())//�ٴ��ж�ͼ���Ƿ�Ϊ��
		return;
	QImage shadow1(px.size(), QImage::Format_ARGB32_Premultiplied);//������Ӱ1����ʽΪARGBԤ�˸�ʽ
	// QImage:Format_ARGB32_Premultiplied��QImage���ж����һ��ͼ���ʽ��
	//ARGB32��ʾÿ��������4���ֽ���ɣ��ֱ����ڴ洢͸���ȣ�Alpha������ɫ��Red������ɫ��Green������ɫ��Blue����ֵ��
	//Premultiplied��ʾ��ɫֵ�Ѿ���͸����ֵ������Ԥ�����㡣
	//���磬���һ�����ص���ɫ�Ǻ�ɫ��255��0��0����͸����Ϊ128��0.5������Ԥ�˸�ʽ�У���洢����ɫֵ���ǣ�128��0��0��

	shadow1.setDevicePixelRatio(px.devicePixelRatioF());//��shadow1���Qlmage������豸���ر�����Ϊ��px��ͬ��ֵ
	//�豸���ر�(DevicePixelRatio�����DPR)������������Ļ�����������߼�����֮��ı�����ϵ
	shadow1.fill(0);//����Ӱ1���Ϊ��ȫ͸������ɫΪ��ɫ
	QImage shadow2(px.size(), QImage::Format_ARGB32_Premultiplied);
	shadow2.setDevicePixelRatio(px.devicePixelRatioF());
	shadow2.fill(0);
	QPoint offset;//����һ��QPoint���͵ı���offset���ڴ洢ƫ����
	qreal radian = angle / 180 * 3.14;//���Ƕ�ת��Ϊ����
	offset.setX(int(distance * qCos(radian)));//����������ƫ����
	offset.setY(int(distance* qSin(radian)));//����Y�����ƫ������DPR)������������Ļ����
	//QT_BEGIN_NAMESPACE
	//	extern Q_WIDGETS_EXPORT void qt_blurlmage(QPainter * p, QImage & blurlmage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
	////�����ⲿ�������ú����ɶ�ͼ����и�˹ģ������
	//QT_END_NAMESPACE
	//QT_BEGIN_NAMESPACE��QT_END_NAMESPACE��Qt��������ڶ��������ռ䷶Χ�ĺ�
	//����������֮�������ķ���(�纯�����ࡢ������)�������ض���Qt�����ռ䣬
	//Q_WIDGETS_EXPORTҲ��һ���꣬ͨ������ָʾ�ú����ǿ��ڿ���ⲿ�����ʵĵ�������
	QPainter shadowPainter(&shadow1);//��shadow1��������
	shadowPainter.setCompositionMode(QPainter::CompositionMode_Source);
	//setCompositionMode������������QPainter�ĺϳ�ģʽ
	//QPainter:CompositionMode_Source��һ�ֺϳ�ģʽ����ʾ���Ƶ�Դͼ�ν���ȫ�滻Ŀ��λ�õ�ԭ������
	shadowPainter.drawPixmap(0, 0, px);
	shadowPainter.end();//ʹ��end��������Դ�ͷ�
	QImage blurred(shadow1.size(), QImage::Format_ARGB32_Premultiplied);//����һ����Ϊģ��ͼ���ͼƬ
	blurred.setDevicePixelRatio(px.devicePixelRatioF());
	blurred.fill(0);
	//QPainter blurPainter(&blurred);//�����ͼ���Ͻ��и�˹ģ��
	//qt_blurlmage(&blurPainter, shadow1, blurRadius, false, true);
	//blurPainter.end();//�ͷ���Դ
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(blurred));
	QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect;
	blurEffect->setBlurRadius(blurRadius); // Adjust the blur radius
	item->setGraphicsEffect(blurEffect);
	shadow1 = std::move(item->pixmap().toImage());
	//���д���ʹ����C++11������ƶ�����
	//std��move�����������ء��ƶ������ݣ����ǽ���ת��Ϊһ����ֵ���ã����߱��������Ǵ������ƶ������Ǹ��Ƶķ�ʽ�������������
	shadowPainter.begin(&shadow1);//��ʼ��shadow1��������
	shadowPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//QPainter:CompositionMode_Sourceln��QPainter��һ�ֺϳ�ģʽ
	//�����ֺϳ�ģʽ�£�ֻ�����Դͼ�κ�Ŀ��ͼ�εĽ������֣�����Դͼ��ֻ�������Ŀ��ͼ���ڲ���Դͼ�ε�͸���Ȼ�Ӱ�����յ���ʾЧ��
	shadowPainter.fillRect(shadow1.rect(), QColor::fromRgbF(0.75, 0.75, 0.75, float(strength)));
	shadowPainter.end();

	//shadow2����벿����Ӱ
	QPainter shadowPainter2(&shadow2);
	shadowPainter2.setCompositionMode(QPainter::CompositionMode_Source);
	shadowPainter2.drawPixmap(-3, -3, px);
	shadowPainter2.end();
	QImage blurred2(shadow2.size(), QImage::Format_ARGB32_Premultiplied);
	blurred2.setDevicePixelRatio(px.devicePixelRatioF());
	blurred2.fill(0);
	/*QPainter blurPainter2(&blurred2);
	qt_blurlmage(&blurPainter2, shadow2, blurRadius, false, true);
	blurPainter2.end();
	shadow2 = std::move(blurred2);*/
	QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(blurred2));
	QGraphicsBlurEffect* blurEffect2 = new QGraphicsBlurEffect;
	blurEffect2->setBlurRadius(blurRadius); // Adjust the blur radius
	item2->setGraphicsEffect(blurEffect2);
	shadow2 = std::move(item2->pixmap().toImage());
	shadowPainter2.begin(&shadow2);
	shadowPainter2.setCompositionMode(QPainter::CompositionMode_SourceIn);
	shadowPainter2.fillRect(shadow2.rect(), QColor::fromRgbF(1.0, 1.0, 1.0, strength));
	shadowPainter2.end();
	painter->drawImage(pos + offset, shadow1);//�ڸ�λ�û���shadow1
	painter->drawImage(pos - offset, shadow2);
	painter->drawPixmap(pos, px);
	painter->setWorldTransform(restoreTransform);
}





CustomButton::CustomButton(int i, QWidget *parent) 
	: QWidget(parent) 
{
	m_Hlayer = new QHBoxLayout(this);
	screen_rect = QGuiApplication::primaryScreen()->geometry();//��Ļ�ߴ�
	//shadow.fill(0);
	this->resize(220, 220);                       // ���ô��ڳߴ�
	this->rect().center() = screen_rect.center();//���ھ���
	this->setStyleSheet("background: #000000;");//���ô��ڱ�����ɫ
	this->setWindowTitle(tr("����̬���ť"));//���ô��ڱ���

    customUi();

	m_Hlayer->addWidget(button1);
    m_Hlayer->addWidget(button2);
}

CustomButton::~CustomButton()
{
}

void CustomButton::buttonOperation()
{
	auto shadow = new Shadow();//������Ӱ����
	button1->setStyleSheet("background:#ebecf0;border:0px;border-radius:10px;");//���ð�ť�������߿򡢱߿�Բ��
	button1->setGraphicsEffect(shadow);//Ӧ����Ӱ
	QString filePath = QDir::currentPath() + "/456.png";//��ȡͼƬ����·��
		button1->setIcon(QIcon(filePath));//����Ϊͼ��
	button1->setIconSize(QSize(35, 35));//����ͼ��ߴ�
	auto shadow2 = new Shadow();
	button2->setStyleSheet("background:#ebecf0;border:0px;border-radius:10px;");
	button2->setGraphicsEffect(shadow2);
	QString filePath2 = QDir::currentPath() + "/456.png";
	button2->setIcon(QIcon(filePath2));
	button2->setIconSize(QSize(35, 35));

	connect(button1, &QPushButton::clicked, this, [=]()//��ť��������
	{
		if(button1->isChecked()){//�����ť������
			button1->setCheckable(false);//���ð�ťΪδ��ѡ��
			button1->setStyleSheet("background:#ebecf0; border:0px; border-radius:10px;");
		}
		else//�����ťδ������
		{
			button1->setCheckable(true);//���ð�ť״̬Ϊѡ��
                  button1->setStyleSheet("background: "
                            "qlineargradient(x1: 0, y1: 0, "
                            "x2: 1, y2: 1, stop: 0 #cccccc, "
                            "stop: 0.5 #ebecf0, stop: 0.8 "
                            "#ffffff, stop: 1 #ffffff);"
                            "border:0px;border-radius:"
                            "10px;"); // ���ð�ť����Ϊ���Խ��䣬�ؼ�����
		}
	});

	connect(button2, &QPushButton::clicked, this, [=]() {
		if (button2->isChecked()) {
			button2->setCheckable(false);
			button2->setStyleSheet("background:#ebecf0; border:0px; border-radius:10px;");
		}
		else{
			button2->setCheckable(true);
			button2->setStyleSheet(
				"background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #cccccc, stop: 0.5 #ebecf0, stop: 0.8 #ffffff, stop: 1 #ffffff);" \
				"border:0px;border-radius:10px;");
		}
	});
		
}

void CustomButton::customUi()
{
	button1 = new QPushButton(this);//������ť����
	button1->resize(50, 50);//���ð�ť�ߴ�
	button1->setText("");//���ð�ť�ı�Ϊ��
	int x1 = this->rect().center().x() - button1->width() / 2 - 30;//���ð�ťx����
	int y1 = this->rect().center().y() - button1->height() / 2;//���ð�ťy����
	button1->move(x1, y1);//����ť�ƶ�������λ��
	button1->show();//��ʾ��ť
	button2 = new QPushButton(this);
	button2->resize(50, 50);
	button2->setText("");
		int x2 = this->rect().center().x() - button2->width() / 2 + 30;
	int y2 = this->rect().center().y() - button2->height() / 2;
	button2->show();
	button2->move(x2, y2);
}