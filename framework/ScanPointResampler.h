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
 * @file ScanPointResampler.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef SCAN_POINT_RESAMPLER_H_
#define SCAN_POINT_RESAMPLER_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Scan2D.h"


class ScanPointResampler
{
private:
  double dthreS;                     // �_�̋����Ԋu[m]
  double dthreL;                     // �_�̋���臒l[m]�B���̊Ԋu�𒴂������Ԃ��Ȃ�
  double dis;                        // �ݐϋ����B��Ɨp

public:
  ScanPointResampler() : dthreS(0.05), dthreL(0.25), dis(0) {
  }

  ~ScanPointResampler() {
  }

///////

  void setDthre(int s, int l) {
    dthreS = s;
    dthreL = l;
  }  

////////

  void resamplePoints(Scan2D *scan);
  bool findInterpolatePoint(const LPoint2D &cp, const LPoint2D &pp, LPoint2D &np, bool &inserted);
};

#endif
