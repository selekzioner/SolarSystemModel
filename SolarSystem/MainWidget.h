#pragma once

#include <QOpenGLWidget>

#include "Camera.h"
#include "SolarSystem.h"
#include "SolarSystemCameraAdapter.h"

class MainWidget final : public QOpenGLWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget* parent = nullptr);

public slots:
  void Disconnect();
  void ConnectWithSun();
  void ConnectWithMercury();
  void ConnectWithVenus();
  void ConnectWithEarth();
  void ConnectWithMars();
  void ConnectWithJupiter();
  void ConnectWithSaturn();
  void ConnectWithUranus();
  void ConnectWithNeptune();

protected:
  void initializeGL() override;
  void paintGL() override;

  //void keyPressEvent(QKeyEvent* event) override;
  //void wheelEvent(QWheelEvent* event) override;

private:
  SolarSystemModel::SolarSystem _solarSystem;
  //Camera _camera;
  SolarSystemModel::SolarSystemCameraAdapter _cameraAdapter;
};

