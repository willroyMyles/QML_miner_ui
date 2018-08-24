/**************************************************************************
This file is part of JahshakaVR, VR Authoring Toolkit
http://www.jahshaka.com
Copyright (c) 2016  GPLv3 Jahshaka LLC <coders@jahshaka.com>

This is free software: you may copy, redistribute
and/or modify it under the terms of the GPLv3 License

For more information see the LICENSE file
*************************************************************************/

#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QProcess>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <functional>

struct MinerChartData
{
	bool connected;
	long time;
	float hps;// hashes per second
};

class QProcess;
enum class MinerStatus
{
	Idle,
	Starting,
	Mining,
	Stopping,
};

enum class GPUType
{
	NVidia,
	AMD
};

struct GPU
{
	int index;
	QString vendor;
	QString name;
	GPUType type;
};


class MinerSettings;
class MinerProcess;
class QTimer;

class MinerManager : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString poolUrlValue READ poolUrlValue WRITE setPoolUrlValue NOTIFY poolUrlValueChanged)
		Q_PROPERTY(QString identifierValue READ identifierValue WRITE setIdentifierValue NOTIFY identifierValueChanged)
		Q_PROPERTY(QString passwordValue READ passwordValue WRITE setPasswordValue NOTIFY passwordValueChanged)
		Q_PROPERTY(QString walletIDValue READ walletIDValue WRITE setWalletIDValue NOTIFY walletIDValueChanged)
signals:
	void poolUrlValueChanged(QString);
	void identifierValueChanged(QString);
	void passwordValueChanged(QString);
	void walletIDValueChanged(QString);
public:

	QString poolUrlValue() { return poolUrl; }
	void setPoolUrlValue(QString string) {
		poolUrl = string;
		poolUrlValueChanged(string);
	}
	QString identifierValue() { return identifier; }
	void setIdentifierValue(QString string) {
		identifier = string;
		identifierValueChanged(string);
	}
	QString passwordValue() { return password; }
	void setPasswordValue(QString string) {
		password = string;
		passwordValueChanged(string);
	}
	QString walletIDValue() { return walletId; }
	void setWalletIDValue(QString string) {
		walletId = string;
		walletIDValueChanged(string);
	}


	QString poolUrl = "165.227.72.177:3333";
	QString identifier = "x";
	QString password = "jahminer";
	//QString walletId = "43QGgipcHvNLBX3nunZLwVQpF6VbobmGcQKzXzQ5xMfJgzfRBzfXcJHX1tUHcKPm9bcjubrzKqTm69JbQSL4B3f6E3mNCbU";
	QString walletId = "43QGgipcHvNLBX3nunZLwVQpF6VbobmGcQKzXzQ5xMfJgzfRBzfXcJHX1tUHcKPm9bcjubrzKqTm69JbQSL4B3f6E3mNCbU";

	QVector<MinerProcess*> processes;

	// initializes a MinerProcess for each miner
	// returns false is there is any error
	bool initialize();
};

class MinerChart;
class MinerProcess : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString poolUrl READ poolUrl WRITE setPoolUrl NOTIFY poolUrlChanged)
public:

	QString poolUrl() { return minerMan->poolUrl; }
	void setPoolUrl(QString string) { minerMan->poolUrl = string; emit poolUrlChanged(string); }


	bool _isMining = false;
	float hashesPerSecond;
	//QString gpuType;
	GPU gpu;

	MinerManager* minerMan;

	// process
	QProcess* process = nullptr;
	QNetworkAccessManager* netMan;

	// for getting http reports
	int networkPort;
	QString networkUrl;
	int sentRequests;

	// number of retries after miner has crashed
	int retries;

	MinerStatus status;

	QVector<MinerChartData> data;
	//MinerChart* minerChart = nullptr;

	// sets gpu and index to mine
	void setGpu(GPU gpu)
	{
		this->gpu = gpu;
	}

	void setNetworkPort(int portNum);

	void startMining();
	void stopMining();
	bool isMining() { return _isMining; }
	MinerStatus getMinerStatus()
	{
		return status;
	}

	QTimer* timer;

	explicit MinerProcess(QObject *parent = Q_NULLPTR) {
		netMan = new QNetworkAccessManager(nullptr);
		sentRequests = 0;
		retries = 0;
	};

	void setManager(MinerManager *manager) {
		minerMan = manager;
	}

	MinerProcess(MinerManager* manager)
	{
		minerMan = manager;
		netMan = new QNetworkAccessManager(nullptr);
		sentRequests = 0;
		retries = 0;
	}

	virtual ~MinerProcess()
	{

	}

signals:
	void minerStatusChanged(MinerStatus status);

	// called as soon as new miner data comes in
	//void onMinerChartData(MinerChartData data);
	void poolUrlChanged(QString);
private:
	void networkRequest(QString url, std::function<void(QString)> successCallback, std::function<void(QNetworkReply::NetworkError)> errorCallback);
	void _setMinerStatus(MinerStatus status);
};

/*
GPUMinerProcess::GPUMinerProcess():
QObject()
{
gpu = MiningGPU::NVidia;
gpuIndex = 0;
}
*/