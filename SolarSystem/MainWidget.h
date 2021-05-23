#pragma once

#include <QLabel>
#include <QOpenGLWidget>

#include "SolarSystem.h"
#include "SolarSystemCameraAdapter.h"

class MainWidget final : public QOpenGLWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget* parent = nullptr);

public slots:
  void ConnectWithSun();
  void ConnectWithMercury();
  void ConnectWithVenus();
  void ConnectWithEarth();
  void ConnectWithMars();
  void ConnectWithJupiter();
  void ConnectWithSaturn();
  void ConnectWithUranus();
  void ConnectWithNeptune();

  void ResetMode();
  void Boost(int factor);

  void SetDemonstrativeView();
  void SetTopView();

signals:
  void SendTimeData(const QString& data);

protected:
  void initializeGL() override;
  void paintGL() override;

  void keyPressEvent(QKeyEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

private:
  SolarSystemModel::SolarSystem _solarSystem;
  SolarSystemModel::SolarSystemCameraAdapter _cameraAdapter;
  SolarSystemModel::SolarSystemMode _mode = SolarSystemModel::SolarSystemMode::Real;

  QLabel _timeLabel;
};

