#include <QKeyEvent>

#include "MainWidget.h"

using namespace SolarSystemModel;

MainWidget::MainWidget(QWidget* parent)
: QOpenGLWidget(parent), _cameraAdapter(_solarSystem)
{
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

void MainWidget::ResetMode()
{
	_mode = _mode == SolarSystemMode::Real ? SolarSystemMode::Demonstrative : SolarSystemMode::Real;
	_solarSystem.Reset(_mode);
	_cameraAdapter.ConnectWithObject("Sun");
}

void MainWidget::Boost(const int factor)
{
	_solarSystem.Boost(static_cast<float>(factor) / 50.f);
}

void MainWidget::initializeGL()
{
	setFocusPolicy(Qt::StrongFocus);
  _solarSystem.Initialize();
	_cameraAdapter.ConnectWithObject("Sun");
}

void MainWidget::paintGL()
{
	_cameraAdapter.Update();
  _solarSystem.Render(_cameraAdapter.GetCamera());
  update();
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
  switch (event->key()) {
	  case Qt::Key_A:
			_cameraAdapter.Rotate({ -1, 0 });
	    break;
	  case Qt::Key_D:
			_cameraAdapter.Rotate({ 1, 0 });
	    break;
	  case Qt::Key_W:
			_cameraAdapter.Rotate({ 0, 1 });
	    break;
	  case Qt::Key_S:
			_cameraAdapter.Rotate({ 0, -1 });
	    break;
  }
}

void MainWidget::wheelEvent(QWheelEvent* event)
{
  if (event->angleDelta().y() > 0)
		_cameraAdapter.Magnify(1);
	
  else if (event->angleDelta().y() < 0)
		_cameraAdapter.Magnify(-1);
}