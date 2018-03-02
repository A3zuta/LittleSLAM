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
 * @file PoseOptimizer.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef _POSE_OPTIMIZER_H_
#define _POSE_OPTIMIZER_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "CostFunction.h"

class PoseOptimizer
{
public:
  int allN;             // �J��Ԃ������B�e�X�g�p
  double sum;           // �c�����v�B�e�X�g�p

protected:
  double evthre;                // �R�X�g�ω�臒l�B�ω��ʂ�����ȉ��Ȃ�J��Ԃ��I��
  double dd;                    // ���l�����̍��݁i���i�j
  double da;                    // ���l�����̍��݁i��]�j

  CostFunction *cfunc;          // �R�X�g�֐�

public:
  PoseOptimizer(): evthre(0.000001), dd(0.00001), da(0.00001), cfunc(nullptr) {
    allN=0; sum=0;
  }

  ~PoseOptimizer() {
  }

/////

  void setCostFunction(CostFunction *f) {
    cfunc = f;
  }

  void setEvlimit(double l) {
    cfunc->setEvlimit(l);
  }

  void setPoints(std::vector<const LPoint2D*> &curLps, std::vector<const LPoint2D*> &refLps) {
    cfunc->setPoints(curLps, refLps);
  }

  void setEvthre(double inthre) {
    this->evthre = inthre;
  }
  double getPnrate() {
    return (cfunc->getPnrate());
  }

  void setDdDa(double d, double a){
    dd = d;
    da = a;
  }

////////

  virtual double optimizePose(Pose2D &initPose, Pose2D &estPose) = 0;
};

#endif 
