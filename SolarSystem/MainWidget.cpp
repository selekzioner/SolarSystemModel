#include <QKeyEvent>

#include "MainWidget.h"

using namespace SolarSystemModel;

MainWidget::MainWidget(QWidget* parent)
: QOpenGLWidget(parent), _cameraAdapter(_solarSystem)
{
	setFocus();
}

void MainWidget::ConnectWithSun()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Sun");
}

void MainWidget::ConnectWithMercury()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Mercury");
}

void MainWidget::ConnectWithVenus()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Venus");
}

void MainWidget::ConnectWithEarth()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Earth");
}

void MainWidget::ConnectWithMars()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Mars");
}

void MainWidget::ConnectWithJupiter()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Jupiter");
}

void MainWidget::ConnectWithSaturn()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Saturn");
}

void MainWidget::ConnectWithUranus()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Uranus");
}

void MainWidget::ConnectWithNeptune()
{
	setFocus();
	_cameraAdapter.ConnectWithObject("Neptune");
}

void MainWidget::ResetMode()
{
	setFocus();
	_mode = _mode == SolarSystemMode::Real ? SolarSystemMode::Demonstrative : SolarSystemMode::Real;
	_solarSystem.Reset(_mode);
	_cameraAdapter.ConnectWithObject("Sun");
	_cameraAdapter.SetDemonstrativeView();
}

void MainWidget::Boost(const int factor)
{
	setFocus();
	_solarSystem.Boost(static_cast<float>(factor) / 50.f);
}

void MainWidget::SetDemonstrativeView()
{
	setFocus();
	_cameraAdapter.SetDemonstrativeView();
}

void MainWidget::SetTopView()
{
	setFocus();
	_cameraAdapter.SetTopView();
}

void MainWidget::initializeGL()
{
	setFocusPolicy(Qt::StrongFocus);
  _solarSystem.Initialize();
	ResetMode();
}

void MainWidget::paintGL()
{
	_cameraAdapter.Update();
  _solarSystem.Render(_cameraAdapter.GetCamera());
	auto time = QString("1 day = ") +
		QString(std::to_string(3.6 / _solarSystem.boostFactor).c_str()) + QString(" sec");
	emit SendTimeData(time);
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
		default: break;
  }
}

void MainWidget::wheelEvent(QWheelEvent* event)
{
  if (event->angleDelta().y() > 0)
		_cameraAdapter.Magnify(1);
	
  else if (event->angleDelta().y() < 0)
		_cameraAdapter.Magnify(-1);
}