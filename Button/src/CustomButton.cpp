#include <QGraphicsPixmapItem>

#include "CustomButton.h"

QRectF Shadow::boundingRectFor(const QRectF& rect) const
{
	return rect.united(rect.translated(0, 0).adjusted(-blurRadius - distance, -blurRadius - distance, blurRadius + distance, blurRadius + distance));
}

void Shadow::draw(QPainter* painter)
{
	PixmapPadMode mode = PadToEffectiveBoundingRect;//创建映射模式
	QPoint pos;
	const QPixmap px = sourcePixmap(Qt::DeviceCoordinates, &pos, mode);//获取源图像
	//Qt::DeviceCoordinates是一个枚举值，表示坐标系统为设备坐标。在Qt中，存在不同的坐标系统，设备坐标是与具体的显示设备相关的坐标，通常以像素为单位。
	if(px.isNull())//判断图像是否为空
		return;
	QTransform restoreTransform = painter->worldTransform();//保存当前画家的世界变换
	painter->setWorldTransform(QTransform());//将世界变换设置为空
	if(px.isNull())//再次判断图像是否为空
		return;
	QImage shadow1(px.size(), QImage::Format_ARGB32_Premultiplied);//定义阴影1，格式为ARGB预乘格式
	// QImage:Format_ARGB32_Premultiplied是QImage类中定义的一种图像格式。
	//ARGB32表示每个像素由4个字节组成，分别用于存储透明度（Alpha）、红色（Red）、绿色（Green）和蓝色（Blue）的值。
	//Premultiplied表示颜色值已经与透明度值进行了预乘运算。
	//例如，如果一个像素的颜色是红色（255，0，0），透明度为128（0.5），在预乘格式中，其存储的颜色值将是（128，0，0）

	shadow1.setDevicePixelRatio(px.devicePixelRatioF());//将shadow1这个Qlmage对象的设备像素比设置为与px相同的值
	//设备像素比(DevicePixelRatio，简称DPR)是用于描述屏幕物理像素与逻辑像素之间的比例关系
	shadow1.fill(0);//将阴影1填充为完全透明且颜色为黑色
	QImage shadow2(px.size(), QImage::Format_ARGB32_Premultiplied);
	shadow2.setDevicePixelRatio(px.devicePixelRatioF());
	shadow2.fill(0);
	QPoint offset;//定义一个QPoint类型的变量offset用于存储偏移量
	qreal radian = angle / 180 * 3.14;//将角度转换为弧度
	offset.setX(int(distance * qCos(radian)));//计算×方向的偏移量
	offset.setY(int(distance* qSin(radian)));//计算Y方向的偏移量称DPR)是用于描述屏幕物理
	//QT_BEGIN_NAMESPACE
	//	extern Q_WIDGETS_EXPORT void qt_blurlmage(QPainter * p, QImage & blurlmage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
	////声明外部函数，该函数可对图像进行高斯模糊处理
	//QT_END_NAMESPACE
	//QT_BEGIN_NAMESPACE和QT_END_NAMESPACE是Qt框架中用于定义命名空间范围的宏
	//在这两个宏之间声明的符号(如函数、类、变量等)都属于特定的Qt命名空间，
	//Q_WIDGETS_EXPORT也是一个宏，通常用于指示该函数是可在库的外部被访问的导出函数
	QPainter shadowPainter(&shadow1);//在shadow1上面作画
	shadowPainter.setCompositionMode(QPainter::CompositionMode_Source);
	//setCompositionMode函数用于设置QPainter的合成模式
	//QPainter:CompositionMode_Source是一种合成模式，表示绘制的源图形将完全替换目标位置的原有内容
	shadowPainter.drawPixmap(0, 0, px);
	shadowPainter.end();//使用end函数将资源释放
	QImage blurred(shadow1.size(), QImage::Format_ARGB32_Premultiplied);//创建一个名为模糊图像的图片
	blurred.setDevicePixelRatio(px.devicePixelRatioF());
	blurred.fill(0);
	//QPainter blurPainter(&blurred);//在这个图像上进行高斯模糊
	//qt_blurlmage(&blurPainter, shadow1, blurRadius, false, true);
	//blurPainter.end();//释放资源
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(blurred));
	QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect;
	blurEffect->setBlurRadius(blurRadius); // Adjust the blur radius
	item->setGraphicsEffect(blurEffect);
	shadow1 = std::move(item->pixmap().toImage());
	//这行代码使用了C++11引入的移动语义
	//std：move并不是真正地“移动”数据，而是将其转换为一个右值引用，告诉编译器我们打算以移动而不是复制的方式来处理这个对象
	shadowPainter.begin(&shadow1);//开始在shadow1上面作画
	shadowPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	//QPainter:CompositionMode_Sourceln是QPainter的一种合成模式
	//在这种合成模式下，只会绘制源图形和目标图形的交集部分，并且源图形只会出现在目标图形内部，源图形的透明度会影响最终的显示效果
	shadowPainter.fillRect(shadow1.rect(), QColor::fromRgbF(0.75, 0.75, 0.75, float(strength)));
	shadowPainter.end();

	//shadow2是左半部分阴影
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
	painter->drawImage(pos + offset, shadow1);//在该位置绘制shadow1
	painter->drawImage(pos - offset, shadow2);
	painter->drawPixmap(pos, px);
	painter->setWorldTransform(restoreTransform);
}





CustomButton::CustomButton(int i, QWidget *parent) 
	: QWidget(parent) 
{
	m_Hlayer = new QHBoxLayout(this);
	screen_rect = QGuiApplication::primaryScreen()->geometry();//屏幕尺寸
	//shadow.fill(0);
	this->resize(220, 220);                       // 设置窗口尺寸
	this->rect().center() = screen_rect.center();//窗口居中
	this->setStyleSheet("background: #000000;");//设置窗口背景颜色
	this->setWindowTitle(tr("新拟态风格按钮"));//设置窗口标题

    customUi();

	m_Hlayer->addWidget(button1);
    m_Hlayer->addWidget(button2);
}

CustomButton::~CustomButton()
{
}

void CustomButton::buttonOperation()
{
	auto shadow = new Shadow();//创建阴影对象
	button1->setStyleSheet("background:#ebecf0;border:0px;border-radius:10px;");//设置按钮背景、边框、边框圆角
	button1->setGraphicsEffect(shadow);//应用阴影
	QString filePath = QDir::currentPath() + "/456.png";//获取图片绝对路径
		button1->setIcon(QIcon(filePath));//设置为图标
	button1->setIconSize(QSize(35, 35));//设置图标尺寸
	auto shadow2 = new Shadow();
	button2->setStyleSheet("background:#ebecf0;border:0px;border-radius:10px;");
	button2->setGraphicsEffect(shadow2);
	QString filePath2 = QDir::currentPath() + "/456.png";
	button2->setIcon(QIcon(filePath2));
	button2->setIconSize(QSize(35, 35));

	connect(button1, &QPushButton::clicked, this, [=]()//按钮匿名函数
	{
		if(button1->isChecked()){//如果按钮被按下
			button1->setCheckable(false);//设置按钮为未被选中
			button1->setStyleSheet("background:#ebecf0; border:0px; border-radius:10px;");
		}
		else//如果按钮未被按下
		{
			button1->setCheckable(true);//设置按钮状态为选中
                  button1->setStyleSheet("background: "
                            "qlineargradient(x1: 0, y1: 0, "
                            "x2: 1, y2: 1, stop: 0 #cccccc, "
                            "stop: 0.5 #ebecf0, stop: 0.8 "
                            "#ffffff, stop: 1 #ffffff);"
                            "border:0px;border-radius:"
                            "10px;"); // 设置按钮背景为线性渐变，关键代码
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
	button1 = new QPushButton(this);//创建按钮对象
	button1->resize(50, 50);//设置按钮尺寸
	button1->setText("");//设置按钮文本为空
	int x1 = this->rect().center().x() - button1->width() / 2 - 30;//设置按钮x坐标
	int y1 = this->rect().center().y() - button1->height() / 2;//设置按钮y坐标
	button1->move(x1, y1);//将按钮移动到坐标位置
	button1->show();//显示按钮
	button2 = new QPushButton(this);
	button2->resize(50, 50);
	button2->setText("");
		int x2 = this->rect().center().x() - button2->width() / 2 + 30;
	int y2 = this->rect().center().y() - button2->height() / 2;
	button2->show();
	button2->move(x2, y2);
}