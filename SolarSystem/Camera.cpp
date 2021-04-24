#include "Camera.h"

QMatrix4x4 Camera::GetViewMatrix() const
{
  QMatrix4x4 matrix;
  matrix.lookAt(pos, pos + front, up);
  return matrix;
}