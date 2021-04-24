#include <QKeyEvent>

#include "MainWidget.h"

MainWidget::MainWidget(QWidget* parent)
: QOpenGLWidget(parent), _cameraAdapter(_solarSystem)
{
}

void MainWidget::Disconnect()
{
  _cameraAdapter.ConnectWithObject("");
}

void MainWidget::ConnectWithSun()
{
	_cameraAdapter.ConnectWithObject("Sun");
}

void MainWidget::ConnectWithMercury()
{
	_cameraAdapter.ConnectWithObject("Mercury");
}

void MainWidget::ConnectWithVenus()
{
	_cameraAdapter.ConnectWithObject("Venus");
}

void MainWidget::ConnectWithEarth()
{
	_cameraAdapter.ConnectWithObject("Earth");
}

void MainWidget::ConnectWithMars()
{
	_cameraAdapter.ConnectWithObject("Mars");
}

void MainWidget::ConnectWithJupiter()
{
	_cameraAdapter.ConnectWithObject("Jupiter");
}

void MainWidget::ConnectWithSaturn()
{
	_cameraAdapter.ConnectWithObject("Saturn");
}

void MainWidget::ConnectWithUranus()
{
	_cameraAdapter.ConnectWithObject("Uranus");
}

void MainWidget::ConnectWithNeptune()
{
	_cameraAdapter.ConnectWithObject("Neptune");
}

void MainWidget::initializeGL()
{
  _solarSystem.Initialize();
  setFocusPolicy(Qt::StrongFocus);
}

void MainWidget::paintGL()
{
	_cameraAdapter.Update();
  _solarSystem.Render(_cameraAdapter.GetCamera());
  update();
}

/*void MainWidget::keyPressEvent(QKeyEvent* event)
{
  const auto angle = 5.f;
  const auto front = _camera.front;
  const auto dir = _camera.front.z() / std::abs(_camera.front.z());

  QMatrix4x4 rotation;
  switch (event->key()) {
	  case Qt::Key_A:
	    rotation.rotate(angle, 0.f, 1.f, 0.f);
	    break;
	  case Qt::Key_D:
	    rotation.rotate(-angle, 0.f, 1.f, 0.f);
	    break;
	  case Qt::Key_W:
	    rotation.rotate(-angle * dir, 1.f, 0.f, 0.f);
	    break;
	  case Qt::Key_S:
	    rotation.rotate(angle * dir, 1.f, 0.f, 0.f);
	    break;
	  default:
	    return;
  }
  _camera.front = rotation * front;
}

void MainWidget::wheelEvent(QWheelEvent* event)
{
  auto dr = 0.f;
  const auto offset = 1.f;
  if (event->angleDelta().y() > 0) {
    dr = offset * _camera.front.z() / abs(_camera.front.z());
  }
  else if (event->angleDelta().y() < 0) {
    dr = -offset * _camera.front.z() / abs(_camera.front.z());
  }
  _camera.pos = { _camera.pos.x() + dr * _camera.front.x(),
                  _camera.pos.y() + dr * _camera.front.y(),
                  _camera.pos.z() + dr * _camera.front.z() };
}*/