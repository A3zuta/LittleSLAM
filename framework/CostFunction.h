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
 * @file CostFunction.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef _COST_FUNCTION_H_
#define _COST_FUNCTION_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"

class CostFunction
{
protected:
  std::vector<const LPoint2D*> curLps;         // �Ή����Ƃꂽ���݃X�L�����̓_�Q
  std::vector<const LPoint2D*> refLps;         // �Ή����Ƃꂽ�Q�ƃX�L�����̓_�Q
  double evlimit;                              // �}�b�`���O�őΉ����Ƃꂽ�ƌ��Ȃ�����臒l
  double pnrate;                               // �덷��evlimit�ȓ��őΉ����Ƃꂽ�_�̔䗦

public:
  CostFunction() : evlimit(0), pnrate(0) {
  }

  ~CostFunction() {
  }

///////

  void setEvlimit(double e) {
    evlimit = e;
  }

  // DataAssociator�őΉ��̂Ƃꂽ�_�Qcur, ref��ݒ�
  void setPoints(std::vector<const LPoint2D*> &cur, std::vector<const LPoint2D*> &ref) {
    curLps = cur;
    refLps = ref;
  }

  double getPnrate() {
    return(pnrate);
  }

///////////

  virtual double calValue(double tx, double ty, double th) = 0;

};

#endif
