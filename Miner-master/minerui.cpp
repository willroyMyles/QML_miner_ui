/**************************************************************************
This file is part of JahshakaVR, VR Authoring Toolkit
http://www.jahshaka.com
Copyright (c) 2016  GPLv3 Jahshaka LLC <coders@jahshaka.com>

This is free software: you may copy, redistribute
and/or modify it under the terms of the GPLv3 License

For more information see the LICENSE file
*************************************************************************/


#include "minerui.h"
#include <QComboBox>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGroupBox>
#include <QSizeGrip>
#include <QStyledItemDelegate>
#include <QStandardPaths>
#include <QMessageBox>
#include <QApplication>
#include <QUuid>
#include <QDesktopServices>
#include "minerprocess.h"


MinerUI::MinerUI(QWidget *parent)
	: QObject(parent)
{
	minerMan = new MinerManager();
	minerMan->initialize();

	settingsMan = new SettingsManager("jahminer.ini");
	fontIcon = new QtAwesome;
    fontIcon->initFontAwesome();

	configureUI();
	configureSettings();
	configureConnections();
	configureStyleSheet();
#ifdef BUILD_AS_LIB
	setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
	setAttribute(Qt::WA_TranslucentBackground);

#else
	//setWindowFlags( Qt::X11BypassWindowManagerHint);
	close->setVisible(false);
	settingsClose->setVisible(false);
	mainLayout->setContentsMargins(0, 0, 0, 0);
#endif

	autoStartSwitch->hide();
	autostart->hide();

	// setWindowFlag(Qt::SubWindow);
	//setWindowModality(Qt::ApplicationModal);

	// add cards
	/*
	for (auto process : minerMan->processes) {
		auto card = this->addGraphicsCard(process->gpu.name);
		card->setMinerProcess(process);
		card->startMining();
	}
	*/
}

MinerUI::~MinerUI()
{
	if (isMining()) stopMining();
}

GraphicsCardUI* MinerUI::addGraphicsCard(QString string)
{
	GraphicsCardUI *card = new GraphicsCardUI();
	card->setCardName(string);
	card->setObjectName(QStringLiteral("card"));
	card->setMinimumHeight(150);
	list.append(card);
	cardHolderLayout->addWidget(card);
	return card;
}

void MinerUI::configureUI()
{



	stack = new QStackedWidget;
	//stack->setGraphicsEffect(effect);
	auto groupBoxLayout = new QVBoxLayout;
	mainLayout = new QVBoxLayout;
	autoLayout = new QVBoxLayout;
	auto bottomLayout = new QHBoxLayout;
	cardHolderLayout = new QVBoxLayout;

	mainLayout->addWidget(stack);

	auto groupBox = new QGroupBox;
	groupBox->setLayout(groupBoxLayout);
	//groupBox->setFixedSize(500, 300);
	//mainLayout->addWidget(groupBox);
	stack->addWidget(groupBox);

	//configure toolbar


	toolbar = new QToolBar();
	toolbar->setObjectName(QStringLiteral("toolBar"));
	settings = new QAction("settings");
	settings->setText(QChar(fa::cog));
	settings->setFont(fontIcon->font(15));
	settings->setToolTip(tr("Click to show settings"));
	advance = new QAction("advance");
	advance->setText(QChar(fa::sliders));
	advance->setFont(fontIcon->font(15));
	//advance->hide();
	close = new QAction("X");
	close->setText(QChar(fa::times));
	close->setFont(fontIcon->font(15));
	close->setToolTip(tr("close button"));

	auto minerLabel = new QLabel("Miner");
	
	toolbar->addAction(settings);
	//toolbar->addAction(advance);
	auto empty = new QWidget();
	empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	toolbar->addWidget(empty);
	toolbar->addWidget(minerLabel);
	auto empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	toolbar->addWidget(empty1);
	toolbar->addAction(close);


	scrollArea = new QScrollArea();
	scrollArea->setContentsMargins(0, 3, 3, 3);
	scrollArea->setAlignment(Qt::AlignTop);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidgetResizable(true);


	cardHolder = new QWidget();
	cardHolder->setObjectName(QStringLiteral("cardHolder"));
	cardHolder->setGeometry(0, 0, 450, 400);
	cardHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	for (int i = 0; i< 2; i++) {
		//addGraphicsCard("amd numbering at this pos " + QString::number(i));
	}
	// todo: move back to top (nick)
	for (auto process : minerMan->processes) {
		auto card = this->addGraphicsCard(process->gpu.name);
		card->setMinerProcess(process);
		//card->startMining();
	}

	cardHolder->setLayout(cardHolderLayout);
	cardHolderLayout->addStretch();
	cardHolderLayout->setContentsMargins(0, 0, 0, 0);
	cardHolderLayout->setSpacing(2);
	scrollArea->setWidget(cardHolder);

	startBtn = new QPushButton("Start");
	startBtn->setToolTip(tr("Click to start mining"));
	coinType = new QLabel("JFX: 0.00123");
	autostart = new QLabel("auto start");
	autostart->setAlignment(Qt::AlignHCenter);
	startBtn->setObjectName(QStringLiteral("startBtn"));

	QFont font = coinType->font();
	font.setStyleStrategy(QFont::PreferAntialias);
	font.setBold(true);
	coinType->setFont(font);
	minerLabel->setFont(font);
	//autostart->setFont(font);


	autoStartSwitch = new Switch();
	autoStartSwitch->setColor(QColor(40, 128, 185));
	autoStartSwitch->setSize(20);
	autoStartSwitch->setChecked(settingsMan->getValue("miner_auto_start", false).toBool());
	auto switchLayout = new QHBoxLayout;
	//switchLayout->addStretch();
	switchLayout->addWidget(autoStartSwitch);
	//switchLayout->addStretch();

	autoLayout->addStretch();
	autoLayout->addLayout(switchLayout);
	autoLayout->addWidget(autostart);
	autoLayout->addStretch();

	auto helpBtn = new QPushButton("Help");
	connect(helpBtn, &QPushButton::pressed, []()
	{
		QDesktopServices::openUrl(QUrl("https://www.jahfx.com/mining"));
	});
	helpBtn->setObjectName(QStringLiteral("startBtn"));

	bottomLayout->addSpacing(10);
	bottomLayout->addWidget(startBtn);
	//bottomLayout->addSpacing(23);
	//bottomLayout->addWidget(coinType);
	bottomLayout->addStretch();
	bottomLayout->addLayout(autoLayout);
	bottomLayout->addWidget(helpBtn);
	bottomLayout->addSpacing(10);

	auto bottomWidget = new QWidget;
	bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	bottomWidget->setLayout(bottomLayout);

	groupBoxLayout->addWidget(toolbar);
	groupBoxLayout->addSpacing(3);
	groupBoxLayout->addWidget(scrollArea);
	groupBoxLayout->addSpacing(3);
	//groupBoxLayout->addLayout(bottomLayout);
	groupBoxLayout->addWidget(bottomWidget);
	//  groupBoxLayout->setSizeConstraint(QLayout::SetFixedSize);
	groupBoxLayout->setSpacing(0);

	auto warningLabel = new QLabel("    If miner behaves unexpectedly, restart application in admin mode.");
	warningLabel->setTextFormat(Qt::RichText);
	warningLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
	warningLabel->setOpenExternalLinks(true);

	auto gripLayout = new QHBoxLayout;
	auto gripWidget = new QWidget;
	gripWidget->setLayout(gripLayout);
	gripLayout->addWidget(warningLabel);


	groupBoxLayout->addWidget(gripWidget);

}

void MinerUI::configureSettings()
{
	auto settingsWidget = new QWidget;
	auto settingsLaout = new QVBoxLayout;
	//settingsLaout->setContentsMargins(10, 6, 10,4 );
	settingsLaout->setSpacing(10);
	settingsWidget->setLayout(settingsLaout);
	settingsWidget->setObjectName(QStringLiteral("settingsWidget"));

	auto toolbar = new QToolBar;
	toolbar->setObjectName(QStringLiteral("toolBar"));

	back = new QAction;
	back->setText(QChar(fa::arrowleft));
	back->setFont(fontIcon->font(15));
	back->setObjectName(QStringLiteral("back"));
	auto settingsLabel = new QLabel("SETTINGS");
//	settingsLabel->setAlignment(Qt::AlignHCenter);
	QFont font = settingsLabel->font();
	font.setBold(true);
	settingsLabel->setFont(font);

	settingsClose = new QAction;
	settingsClose->setText(QChar(fa::times));
	settingsClose->setFont(fontIcon->font(15));
	settingsClose->setObjectName(QStringLiteral("back"));

	connect(settingsClose, SIGNAL(triggered()), close, SLOT(trigger()));
	connect(settingsClose, &QAction::triggered, [this]() {
	});

	auto confirm = new QPushButton("Confirm");
	auto CancelBtn = new QPushButton("Cancel");
	confirm->setObjectName(QStringLiteral("bottomBtn"));
	CancelBtn->setObjectName(QStringLiteral("bottomBtn"));

	connect(confirm, &QPushButton::clicked, [=]() {
		stack->setCurrentIndex(0);
		this->saveAndApplySettings();
	});
	connect(CancelBtn, &QPushButton::clicked, [=]() {
		stack->setCurrentIndex(0);
		this->restoreSettings();
	});


	toolbar->addAction(back);
	back->setToolTip(tr("Click to show details"));
	auto empty = new QWidget();
	empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	toolbar->addWidget(empty);	
	toolbar->addWidget(settingsLabel);
	auto empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	toolbar->addWidget(empty1);
	toolbar->addAction(settingsClose);
	settingsClose->setToolTip(tr("Click to close"));


	auto walletLabel = new QLabel("Wallet Id ");
	auto password = new QLabel("Password ");
	auto poolUrl = new QLabel("Pool URL ");
	auto identifier = new QLabel("Identifier ");
	auto currencyLabel = new QLabel("currency");
	walletLabel->setObjectName(QStringLiteral("label"));
	password->setObjectName(QStringLiteral("label"));
	poolUrl->setObjectName(QStringLiteral("label"));
	identifier->setObjectName(QStringLiteral("label"));
	currencyLabel->setObjectName(QStringLiteral("label"));
	walletLabel->setFont(font);
	password->setFont(font);
	poolUrl->setFont(font);
	identifier->setFont(font);
	currencyLabel->setFont(font);

	walletEdit = new QLineEdit();
	passwordEdit = new QLineEdit();
	poolEdit = new QLineEdit();
	identifierEdit = new QLineEdit();

	QStyledItemDelegate *itemDelegate = new QStyledItemDelegate();
	currency = new QComboBox;
	currency->setItemDelegate(itemDelegate);
	currency->setObjectName(QStringLiteral("currencyBox"));
	auto stringList = QStringList() << "Monero7" << "Aeon" << "BBSCoin" << "Croat" << "Edollar" << "Electroneum" << "Graft" << "Haven" << "Intense" << "Karbo" << "Sumokoin" ;
	currency->setCurrentText("Select Currency");
	currency->addItems(stringList);

	auto walletLayout = new QVBoxLayout;
	auto poolLayout = new QVBoxLayout;
	auto passwordLayout = new QVBoxLayout;
	auto identifierLayout = new QVBoxLayout;
	auto currencyLayout = new QHBoxLayout;
	auto buttonLayout = new QHBoxLayout;

	walletEdit->setObjectName(QStringLiteral("edit"));
	poolEdit->setObjectName(QStringLiteral("edit"));
	passwordEdit->setObjectName(QStringLiteral("edit"));
	identifierEdit->setObjectName(QStringLiteral("edit"));

	walletEdit->setPlaceholderText("Enter Wallet ID");
	poolEdit->setPlaceholderText("Enter Pool URL");
	passwordEdit->setPlaceholderText("Enter Password");
	identifierEdit->setPlaceholderText("Enter Identifier");	 

	walletLayout->addWidget(walletLabel);
	walletLayout->addWidget(walletEdit);
	poolLayout->addWidget(poolUrl);
	poolLayout->addWidget(poolEdit);
	passwordLayout->addWidget(password);
	passwordLayout->addWidget(passwordEdit);
	identifierLayout->addWidget(identifier);
	identifierLayout->addWidget(identifierEdit);
	buttonLayout->addWidget(confirm);
	buttonLayout->addWidget(CancelBtn);
	currencyLayout->addWidget(currencyLabel);
	currencyLayout->addWidget(currency);

	settingsLaout->addWidget(toolbar);
	settingsLaout->addStretch();
	settingsLaout->addLayout(walletLayout);
	settingsLaout->addLayout(poolLayout);
	settingsLaout->addLayout(passwordLayout);
	settingsLaout->addLayout(identifierLayout);
//	settingsLaout->addLayout(currencyLayout);  
	settingsLaout->addStretch();
	settingsLaout->addLayout(buttonLayout);

	stack->addWidget(settingsWidget);

	// pass application settings to ui
	walletIdText = settingsMan->getValue("wallet_id", Constants::MINER_DEFAULT_WALLET_ID).toString();
	walletEdit->setText(walletIdText);
	poolText = settingsMan->getValue("pool", Constants::MINER_DEFAULT_POOL).toString();
	poolEdit->setText(poolText);
	passwordText = settingsMan->getValue("password", Constants::MINER_DEFAULT_PASSWORD+"-"+ generateGUID()).toString();
	passwordEdit->setText(passwordText);
	identifierText = settingsMan->getValue("identifier", "").toString();
	identifierEdit->setText(identifierText);

	minerMan->walletId = walletIdText;
	minerMan->poolUrl = poolText;
	minerMan->password = passwordText;
	minerMan->identifier = identifierText;
}

QString MinerUI::generateGUID() {
	auto id = QUuid::createUuid();
	auto guid = id.toString().remove(0, 1);
	guid.chop(1);
	guid = guid.replace("-", "");
	guid = guid.left(8);
	return guid;
}

void MinerUI::configureConnections()
{
	connect(settings, &QAction::triggered, [this]() {
		stack->setCurrentIndex(1);
		
	});

	connect(back, &QAction::triggered, [this]() {
		resetSettings();
		stack->setCurrentIndex(0);
	});

	


	connect(currency, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {

	});

	connect(advance, SIGNAL(triggered(bool)), this, SLOT(switchToAdvanceMode()));
	connect(close, &QAction::triggered, [this]() {
#ifdef BUILD_AS_LIB
		hide();
#else
		QApplication::exit();
#endif
	});
	/*
	connect(settingsClose, &QAction::triggered, [this]() {
		hide();
	});
	*/

	connect(startBtn, &QPushButton::clicked, [this]() {
		if (!mining) {
			QDir basePath = QDir(QCoreApplication::applicationDirPath());
			auto xmrPath = QDir::cleanPath(basePath.absolutePath() + QDir::separator() + "xmr-stak/xmr-stak.exe");
			if (!QFile::exists(xmrPath)) {

#if defined QT_DEBUG
			//	QMessageBox::warning(this, "xmrstak not found!", "xmrstak is missing or hasnt been compiled.");
#else
				QMessageBox::warning(this, "xmrstak not found!", "xmrstak is missing");
#endif	
				return;
			}
			startMining();
			startButtonStatus = true;
		}
		else {
			stopMining();
			startButtonStatus = false;
		}

	});

	connect(autoStartSwitch, &Switch::onChanged, [this](bool val) {
		startAutomatically = val;
		this->settingsMan->setValue("miner_auto_start", val);
	});

	foreach(card, list) {
		connect(card, &GraphicsCardUI::switchIsOn, [this](bool val) {
			//do something;
			checkList();
		});
	}
}

void MinerUI::configureStyleSheet()
{
	//setStyleSheet("*{color:rgba(255,255,255)}"
	//	"QGroupBox, #settingsWidget{ background: rgba(33,33,33,1); margin:0px; padding : 0px; border: 0px solid black; }"
	//	"QScrollArea, #cardHolder{ border: 1px solid rgba(130,130,130,0); background: rgba(17,17,17,0); border-radius:1px; }"
	//	"#cardHolder, #grip {background: rgba(17,17,17,0); padding: 0px; margin: 0px; }"
	//	"QLabel{ color: rgba(255,255,255,.9); }"
	//	"QLabel#label{ padding-left: 10px; background:rgba(10,10,10,0); }"
	//	"QToolButton, #back {border-radius: 1px; background: rgba(20,20,20, 0); color: rgba(250,250,250, 1); border : 0px solid rgba(20,20,20, 1); padding: 4px 6px 4px 6px ; margin-right:3px;}"
	//	//     "QToolButton:hover{background: rgba(48,48,48, 1);}"
	//	"QScrollBar::handle {background: rgba(40,128, 185,.9); border-radius: 4px; right: 1px; width: 8px;}"
	//	"QScrollBar{border : 0px solid black; background-color: rgba(32,32,32,.1); width: 8px;padding: 1px;}"
	//	"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: rgba(200,200,200,0);}"
	//	"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: rgba(0,0,0,0); border: 0px solid white;}"
	//	"QScrollBar::sub-line, QScrollBar::add-line {background: rgba(10,0,0,.1);}"
	//	"QPushButton{ background: rgba(20,20,20,1); border: 1px solid rgba(10,10,10,1); border-radius: 1px;  color: rgba(255,255,255,.9); padding : 3px 9px 3px 9px; }"
	//	""
	//	"#startBtn{ padding: 9px 19px 9px 19px; background:rgba(23,23,23,.7); border:1px solid rgba(0,0,0,0);}"
	//	"#startBtn:hover, QToolButton:hover, #back:hover { background : rgba(40,128, 185,.9); }"
	//	//   "QScrollArea{background: rgba(23,23,23,1); border: 0px solid black; }"
	//	"#toolBar{ background: rgba(40,128, 185,0); border: 1px solid rgba(10,0,0,0); }"
	//	//"#back{ background: rgba(40,128, 185,0); border: 0px solid rgba(40,40,40,0.3); }"
	//	"#bottomBtn{border: 1px solid rgba(40,40,40,0.3); padding: 10px; }"
	//	"#bottomBtn:hover{background: rgba(40,128, 185,0.5);}"
	//	"#edit { background: rgba(17,17,17,1); margin-left :10; margin-right : 10px; border : 0px; border-bottom : 1px solid black; }"
	//	"#currencyBox, #currencyBox:drop-down {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; }"
	//	"#currencyBox QAbstractItemView {background-color: rgba(33,33,33,1); border :0px; border-bottom: 1px solid black; padding-left: 10px; margin-left : 5px; selection-background-color: rgba(40,128, 185,0); }"
	//	"#currencyBox QAbstractItemView::item:hover {background-color: rgba(40,128,185,1); border :0px;  }"
	//	"QMessageBox{background:rgba(33,33,33,1);}"
	//	"");
}

void MinerUI::resetSettings()
{
	walletIdText = settingsMan->getValue("wallet_id", Constants::MINER_DEFAULT_WALLET_ID).toString();
	walletEdit->setText(walletIdText);
	poolText = settingsMan->getValue("pool", Constants::MINER_DEFAULT_POOL).toString();
	poolEdit->setText(poolText);
	passwordText = settingsMan->getValue("password", "").toString();
	passwordEdit->setText(passwordText);
	identifierText = settingsMan->getValue("identifier", "").toString();
	identifierEdit->setText(identifierText);
}

void MinerUI::closeEvent(QCloseEvent * event)
{
	QApplication::exit();
}

void MinerUI::saveAndApplySettings()
{
	walletIdText = walletEdit->text();
	settingsMan->setValue("wallet_id", walletIdText);
	poolText = poolEdit->text();
	settingsMan->setValue("pool", poolText);
	passwordText = passwordEdit->text();
	settingsMan->setValue("password", passwordText);
	identifierText = identifierEdit->text();
	settingsMan->setValue("identifier", identifierText);

	minerMan->walletId = walletIdText;
	minerMan->poolUrl = poolText;
	minerMan->password = passwordText;
	minerMan->identifier = identifierText;

	//restart mining
	if (isMining()) {
		restartMining();
	}
}

void MinerUI::restoreSettings()
{
	settingsMan->setValue("wallet_id", walletIdText);
	settingsMan->setValue("pool", poolText);
	settingsMan->setValue("password", passwordText);
	settingsMan->setValue("identifier", identifierText);
}

void MinerUI::restartMining()
{
	this->stopMining();
	this->startMining();
}

void MinerUI::startMining()
{
	foreach(card, list) card->setOn(true);
	foreach(card, list) card->startMining();

	startBtn->setText("Stop");
	mining = true;
}

void MinerUI::stopMining()
{
	foreach(card, list) card->setOn(false);
	foreach(card, list) card->stopMining();

	startBtn->setText("Start");
	mining = false;
}

void MinerUI::switchToAdvanceMode()
{
	if (!isInAdvanceMode) {
		foreach(card, list)   card->expand();
		isInAdvanceMode = true;
	}
	else {
		foreach(card, list)   card->contract();
		isInAdvanceMode = false;
	}


}

void Dot::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setPen(QPen(color, 6));
	painter.drawEllipse(3, 4, 7, 7);
}

void Dot::setColor(QColor col) {
	color = col;
	repaint();
}

Dot::Dot(QColor col, QWidget *parent) :QWidget(parent) {
	setFixedSize(15, 15);
	color = col;
}

GraphicsCardUI::GraphicsCardUI(QWidget *parent) : QWidget(parent) {
	configureCard();
	configureConnections();
	setColor(MinerConnection::Notconnected);
	contract();
	switchBtn->simulateClick();
}

void GraphicsCardUI::setCardName(QString name) {
	cardName->setText(name);
	repaint();
}

void GraphicsCardUI::setOn(bool value)
{
	on = value;
}

void GraphicsCardUI::expand() {
	additional->show();
}

void GraphicsCardUI::contract() {
	additional->hide();
}

void GraphicsCardUI::setSpeed(double rate) {
	speed->setText("Speed: " + QString::number(rate) + " H/s");
}

void GraphicsCardUI::setArmed(bool armed) {
	this->armed = armed;
	if (!armed) {
		process->stopMining();
		setMinerStatus(MinerConnection::Notconnected);
	}
}

void GraphicsCardUI::setMinerStatus(MinerConnection con) {
	setColor(con);
}

void GraphicsCardUI::hideLabel() {
	displayLabel->hide();
}

void GraphicsCardUI::showLabel() {
	displayLabel->show();
}

void GraphicsCardUI::setStarted(bool val) {

	if (armed && val)
	{
		mining = val;
		if (process != nullptr) {
			process->startMining();
			setHighlight(true);
		}
	}
	else {
		if (process != nullptr) {
			if (process->isMining()) {
				process->stopMining();
				setHighlight(false);
			}
		}
	}
}

void GraphicsCardUI::setHighlight(bool val) {
	logo->setCheckable(true);
	logo->setChecked(val);
	//displayLabel->setText(val ? "--Mining--" : oldString);
}

void GraphicsCardUI::setMinerProcess(MinerProcess* process)
{
	this->process = process;

	if (process != nullptr) {
		//connect(process, &MinerProcess::onMinerChartData, [this](MinerChartData data)
		//{
		//	// set last hash to ui
		//	this->setSpeed(data.hps);

		//	// if hps is 0 then it must be connecting
		//	// set pool color to orange
		//	if (data.connected && data.hps > 0)
		//		this->setMinerStatus(MinerConnection::Mining);
		//	else
		//		this->setMinerStatus(MinerConnection::Connecting);

		//	if (data.hps != 0) {
		//		if (this->info->data.size() > 100)
		//			this->info->data.removeFirst();
		//		this->info->data.append(data);
		//		this->info->repaint();
		//	}
		//});

		connect(process, &MinerProcess::minerStatusChanged, [this](MinerStatus status)
		{
			switch (status)
			{
			case MinerStatus::Idle:
				this->setMinerStatus(MinerConnection::Inactive);
				displayLabel->setText("Inactive");
				break;
			case MinerStatus::Starting:
				this->setMinerStatus(MinerConnection::Connecting);
				displayLabel->setText("Connecting");
				break;
			case MinerStatus::Mining:
				this->setMinerStatus(MinerConnection::Mining);
				displayLabel->setText("Mining");
				break;
			case MinerStatus::Stopping:
				this->setMinerStatus(MinerConnection::Notconnected);
				displayLabel->setText("Not Connected");
				break;
			}
		});
	}
}

void GraphicsCardUI::startMining()
{
	if (armed) {
		process->startMining();
		setHighlight(true);
	}
}

void GraphicsCardUI::stopMining()
{
	process->stopMining();
	setMinerStatus(MinerConnection::Inactive);
	setHighlight(false);
}

void GraphicsCardUI::setColor(MinerConnection status) {
	switch (status) {
	case MinerConnection::Mining:
		color.setRgb(0, 120, 0, 255);
		displayLabel->setText(tr("Mining"));
		break;
	case MinerConnection::Connecting:
		color.setRgb(255, 120, 70, 255);
		displayLabel->setText(tr("Connecting"));
		break;
	case MinerConnection::Notconnected:
		color.setRgb(170, 1, 2, 255);
		displayLabel->setText(tr("Not Connected"));
		break;
	case MinerConnection::Inactive:
		color.setRgb(240, 240, 240, 255);
		displayLabel->setText(tr("Inactive"));
		break;
	}

	dot->setColor(color);

}

bool GraphicsCardUI::isMining()
{
	return process->isMining();
}

bool GraphicsCardUI::getSwitchStatus()
{
	return switchBtn->on();
}

void GraphicsCardUI::configureCard() {

	// QVBoxLayout *cardLayout = new QVBoxLayout;
	QHBoxLayout *mainLayout = new QHBoxLayout;
	QHBoxLayout *sliderLayout = new QHBoxLayout;
	QVBoxLayout *logoLayout = new QVBoxLayout;
	QVBoxLayout *infoLayout = new QVBoxLayout;
	auto poolDotLayout = new QHBoxLayout;

	auto card = new QWidget;
	auto cardLayout = new QGridLayout;
	card->setLayout(cardLayout);
	card->setObjectName(QStringLiteral("card"));
	card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	displayLabel = new QLabel("");

	auto toolBar = new QWidget;
	toolBar->setObjectName(QStringLiteral("cardBar"));
	auto toolBarLayout = new QHBoxLayout;
	toolBar->setLayout(toolBarLayout);
	toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	logo = new QPushButton();
	logo->setObjectName(QStringLiteral("logo"));
	logo->setLayout(logoLayout);
	logo->setFixedSize(150, 118);
	//logo->setCheckable(true);
	//logo->setCursor(Qt::PointingHandCursor);
	logo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
	//logo->blockSignals(true);


	pool = new QLabel("Pool  ");
	pool->setAlignment(Qt::AlignLeft);
	dot = new Dot(color);
	poolDotLayout->addWidget(pool);
	poolDotLayout->addWidget(dot);
	poolDotLayout->setSpacing(2);
	setMinerStatus(MinerConnection::Notconnected);

	speed = new QLabel("Speed: ");
	speed->setAlignment(Qt::AlignLeft);
	cardName = new QLabel("AMD A9");
	cardName->setAlignment(Qt::AlignHCenter);
	cardName->setWordWrap(true);
	cardName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QFont font = cardName->font();
	font.setStyleStrategy(QFont::PreferAntialias);
	//font.setBold(true);
	cardName->setFont(font);
	font.setBold(false);
	font.setPixelSize(12);
	pool->setFont(font);
	speed->setFont(font);

	switchBtn = new Switch();
	switchBtn->setColor(QColor(40, 128, 185));
	switchBtn->setSize(22);
	sliderLayout->addStretch();
	sliderLayout->addWidget(switchBtn);
	sliderLayout->addStretch();


	//logoLayout->addStretch();
	logoLayout->addWidget(cardName);
	logoLayout->addLayout(poolDotLayout);
	logoLayout->addWidget(speed);
	logoLayout->addLayout(sliderLayout);
	//logoLayout->addStretch();

	//info = new QWidget();
	info = new MinerChart();
	info->setObjectName(QStringLiteral("info"));
	info->setLayout(infoLayout);
	info->setFixedHeight(98);
	info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	infoLayout->setContentsMargins(2, 2, 2, 0);

	additional = new QWidget();
	additional->setObjectName(QStringLiteral("additional"));
	additional->setMinimumHeight(80);
	additional->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	displayLabel->setAlignment(Qt::AlignHCenter);
	displayLabel->setObjectName(QStringLiteral("gpuLabel"));
	font.setBold(true);
	displayLabel->setFont(font);
	infoLayout->addWidget(displayLabel);
	oldString = displayLabel->text();

	toolBarLayout->addWidget(logo);
	toolBarLayout->addWidget(info);

	cardLayout->addWidget(toolBar);
	cardLayout->addWidget(additional);

	// mainLayout->addWidget(logo);
	// mainLayout->addWidget(info);
	//        cardLayout->addLayout(mainLayout);
	//        cardLayout->addWidget(additional);
	//        cardLayout->setSpacing(6);
	//cardLayout->setSizeConstraint(QLayout::SetFixedSize);
	cardLayout->setContentsMargins(2, 1, 3, 2);
	setLayout(mainLayout);
	mainLayout->addWidget(card);

	card->setMinimumHeight(150);
	//card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//qDebug() << card->geometry();
	setStyleSheet(" * {color: white; }"
		"QWidget#logo, QWidget#info,QWidget#additional  { background:rgba(17,17,17,0); border : 0px solid rgba(00,00,00,.2); border-radius: 1px; margin: 0px;  }"
		//"QWidget#logo:hover, QWidget#info:hover,QWidget#additional:hover{border : 1px solid rgba(40,128,185,.01); }"
		//"QLabel{ color:rgba(255,255,255,.8); padding :3px; }"
		"QWidget#info  { border-left : 5px solid rgba(00,00,00,.1);  }"
		"#card:hover{background: rgba(40,128,185,.11); }"
		"#logo:checked {background: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 1, stop: 0 rgba(40,128,185,.5), stop: 0.5 rgba(17,17,17,0));}"
		"QToolBar::separator{ background:rgba(0,0,0,.1);}"
		"#card{background: rgba(40,128,185,.1); border: 1px solid rgba(0,0,0,.85);}"
		"#gpuLabel{ color: rgba(150,150,170,.8);}");

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(0);
	effect->setColor(QColor(0, 0, 0));
	setMinerStatus(MinerConnection::Inactive);
}

void GraphicsCardUI::configureConnections() {

	connect(switchBtn, &Switch::onChanged, [this](bool val) {
		armed = val;
		
		//	logo->setChecked(val);
		if (!val && process->isMining() && process) stopMining(); // if card witch is toggled off and is mining

		if (val && on) startMining(); // if card switch is toggled on and start button pressed

//		displayLabel->setText(val ? "GPU set to mine" : "GPU is not set to mine");
		oldString = displayLabel->text();
		emit switchIsOn(val);

	});



	connect(logo, &QPushButton::clicked, [=]() {
	/*	logo->setChecked(!switchBtn->on());
		qDebug() << switchBtn->on();
		switchBtn->simulateClick();*/
	});


}

void MinerUI::checkList()
{
	if (!isMining()) return;
	for(int i = 0; i < list.size(); i++){
		if (list.at(i)->getSwitchStatus()) {
			return;
		}
	}
	if(startButtonStatus)startBtn->animateClick();
}
