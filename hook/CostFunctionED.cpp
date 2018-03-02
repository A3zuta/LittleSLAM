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
 * @file CostFunctionED.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "CostFunctionED.h"

using namespace std;

// �_�ԋ����ɂ��ICP�̃R�X�g�֐�
double CostFunctionED::calValue(double tx, double ty, double th) {
  double a = DEG2RAD(th);
  double error=0;
  int pn=0;
  int nn=0;
  for (size_t i=0; i<curLps.size(); i++) {
    const LPoint2D *clp = curLps[i];             // ���݃X�L�����̓_
    const LPoint2D *rlp = refLps[i];             // clp�ɑΉ�����Q�ƃX�L�����̓_

    double cx = clp->x;
    double cy = clp->y;
    double x = cos(a)*cx - sin(a)*cy + tx;       // clp���Q�ƃX�L�����̍��W�n�ɕϊ�
    double y = sin(a)*cx + cos(a)*cy + ty;

    double edis = (x - rlp->x)*(x - rlp->x) + (y - rlp->y)*(y - rlp->y);     // �_�ԋ���

    if (edis <= evlimit*evlimit)
      ++pn;                                      // �덷���������_�̐�

    error += edis;                               // �e�_�̌덷��ݐ�

    ++nn;
  }

  error = (nn>0)? error/nn : HUGE_VAL;           // ���ς��Ƃ�B�L���_����0�Ȃ�A�l��HUGE_VAL
  pnrate = 1.0*pn/nn;                            // �덷���������_�̔䗦

//  printf("CostFunctionED: error=%g, pnrate=%g, evlimit=%g\n", error, pnrate, evlimit);     // �m�F�p

  error *= 100;                                  // �]���l���������Ȃ肷���Ȃ��悤100������B

  return(error);
}
