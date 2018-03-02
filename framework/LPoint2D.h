/****************************************************************************
 * LittleSLAM: 2D-Laser SLAM for educational use
 * Copyright (C) 2017-2018 Masahiro Tomono
 * Copyright (C) 2018 Future Robotics Technology Center (fuRo),
 *                    Chiba Institute of Technology.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * @file LPoint2D.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef LPOINT2D_H_
#define LPOINT2D_H_

////////////////////////

struct Vector2D
{
  double x,y;
};

////////////////////////

enum ptype {UNKNOWN=0, LINE=1, CORNER=2, ISOLATE=3};    // �_�̃^�C�v�F���m�A�����A�R�[�i�A�Ǘ�

struct LPoint2D
{
  int sid;                 // �t���[���ԍ��i�X�L�����ԍ��j
  double x;                // �ʒux
  double y;                // �ʒuy
  double nx;               // �@���x�N�g��
  double ny;               // �@���x�N�g��
  double atd;              // �ݐϑ��s����(accumulated travel distance)
  ptype type;              // �_�̃^�C�v

  LPoint2D() : sid(-1), x(0), y(0) {
    init();
  }

  LPoint2D(int id, double _x, double _y): x(_x), y(_y) {
    init();
    sid = id;
  }
 
//////////

  void init() {
    sid = -1;
    atd = 0;
    type = UNKNOWN;
    nx = 0;
    ny = 0;
  }

  void setData(int id, double _x, double _y) {
    init();
    sid = id;
    x = _x;
    y = _y;
  }

  void setXY(double _x, double _y) {
    x = _x;
    y = _y;
  }

  // range��angle����xy�����߂�(�E��n)
  void calXY(double range, double angle) {
    double a = DEG2RAD(angle);
    x = range*cos(a);
    y = range*sin(a);
  }

  // range��angle����xy�����߂�(����n�j
  void calXYi(double range, double angle) {
    double a = DEG2RAD(angle);
    x = range*cos(a);
    y = -range*sin(a);
  }

  void setSid(int i) {
    sid = i;
  }

  void setAtd(double t) {
    atd = t;
  }

  void setType(ptype t) {
    type = t;
  }

  void setNormal(double x, double y) {
    nx = x;
    ny = y;
  }

};

#endif
