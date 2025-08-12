final double QUAT_EPSILON = 0.000001;

double quat_mag(double[] q) {
  return Math.sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
}

boolean quat_dot_eq(double dotprod) {
  return dotprod > 1-QUAT_EPSILON;
}

double quat_dot(double[] q1, double[] q2) {
  return (q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2] + q1[3]*q2[3]);
}

boolean quat_equals(double[] q1, double[] q2) {
  return quat_dot_eq(quat_dot(q1, q2));
}

double[] quat_normalize(double[] q) {
  double invmag = 1.0/quat_mag(q);
  double[] qn = new double[4];
  if (invmag > QUAT_EPSILON) {
    qn[0] = q[0]*invmag;
    qn[1] = q[1]*invmag;
    qn[2] = q[2]*invmag;
    qn[3] = q[3]*invmag;
  }
  return qn;
}

double[] quat_invert(double[] q) {
  return new double[] {-q[0], -q[1], -q[2], q[3]};
}

double[] quat_mult(double[] q1, double[] q2) {
  double[] q3 = new double[] {
    q1[0]*q2[3] + q1[3]*q2[0] + q1[1]*q2[2] - q1[2]*q2[1],
    q1[1]*q2[3] + q1[3]*q2[1] + q1[2]*q2[0] - q1[0]*q2[2],
    q1[2]*q2[3] + q1[3]*q2[2] + q1[0]*q2[1] - q1[1]*q2[0],
    q1[3]*q2[3] - q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2]
  };
  return q3;
}

double quat_angle_between(double[] q1, double[] q2) {
  //double dotprod = Math.max(Math.min(quat_dot(q1, q2), 1), -1);
  //return quat_dot_eq(dotprod) ? 0 : Math.acos(dotprod);
  double[] q1to2 = quat_mult(quat_invert(q1), q2);
  double angle = 2*Math.acos(q1to2[3]);
  if (angle > Math.PI) {
    angle -= 2.0*Math.PI;
  } else if (angle < -Math.PI) {
    angle += 2.0*Math.PI;
  }
  return Math.abs(angle);
}

double[] quat_from_axis_angle(double x, double y, double z, double angle) {
  double len = Math.sqrt(x*x + y*y + z*z);
  if (len > 0.0) {
    x /= len;
    y /= len;
    z /= len;
  }
  
  double half = angle*0.5;
  double sin_val = Math.sin(half);
  double[] q = {
    x * sin_val,
    y * sin_val,
    z * sin_val,
    Math.cos(half)
  };
  double sign = q[3] < 0 ? -1.0 : 1.0;
  for(int i = 0; i < q.length; i++) {
    q[i] *= sign;
  }
  return q;
}

double[] quat_to_axis_angle(double[] q) {
  double mag = Math.sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2]);
  if (mag > 0.0) {
    double ax = q[0]/mag;
    double ay = q[1]/mag;
    double az = q[2]/mag;
    double angle = 2*Math.atan2(mag, q[3]);
    return new double[] { ax, ay, az, angle };
  }
  return new double[] {0, 0, 0, 0};
}

PMatrix3D quat_to_mat(double[] q) {
  float x2 = (float) (q[0]+q[0]);
  float y2 = (float) (q[1]+q[1]);
  float z2 = (float) (q[2]+q[2]);
  float xx2 = (float) (q[0]*x2);
  float yy2 = (float) (q[1]*y2);
  float zz2 = (float) (q[2]*z2);
  float yz2 = (float) (q[1]*z2);
  float wx2 = (float) (q[3]*x2);
  float xy2 = (float) (q[0]*y2);
  float wz2 = (float) (q[3]*z2);
  float xz2 = (float) (q[0]*z2);
  float wy2 = (float) (q[3]*y2);
  PMatrix3D mat = new PMatrix3D(
    1-yy2-zz2, xy2+wz2, xz2-wy2, 0,
    xy2-wz2, 1-xx2-zz2, yz2+wx2, 0,
    xz2+wy2, yz2-wx2, 1-xx2-yy2, 0,
    0, 0, 0, 1
    );
  return mat;
}

double[] quat_from_mat(PMatrix3D mat) {
  double x, y, z, w;
  if (mat.m00 + mat.m11 + mat.m22 > 0) {
    double t = mat.m00 + mat.m11 + mat.m22 + 1;
    double s = 0.5/Math.sqrt(t);
    w = s*t;
    z = (mat.m01 - mat.m10)*s;
    y = (mat.m20 - mat.m02)*s;
    x = (mat.m12 - mat.m21)*s;
  } else if (mat.m00 > mat.m11 && mat.m00 > mat.m22) {
    double t = mat.m00 - mat.m11 - mat.m22 + 1;
    double s = 0.5/Math.sqrt(t);
    x = s*t;
    y = (mat.m01 + mat.m10)*s;
    z = (mat.m20 + mat.m02)*s;
    w = (mat.m12 - mat.m21)*s;
  } else if (mat.m11 > mat.m22) {
    double t = -mat.m00 + mat.m11 - mat.m22 + 1;
    double s = 0.5/Math.sqrt(t);
    y = s*t;
    x = (mat.m01 + mat.m10)*s;
    w = (mat.m20 - mat.m02)*s;
    z = (mat.m12 + mat.m21)*s;
  } else {
    double t = -mat.m00 - mat.m11 + mat.m22 + 1;
    double s = 0.5/Math.sqrt(t);
    z = s*t;
    w = (mat.m01 - mat.m10)*s;
    x = (mat.m20 + mat.m02)*s;
    y = (mat.m12 + mat.m21)*s;
  }
  return new double[] {x, y, z, w};
}
