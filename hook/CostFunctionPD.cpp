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
 * @file CostFunctionPD.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "CostFunctionPD.h"

using namespace std;

// ���������ɂ��R�X�g�֐�
double CostFunctionPD::calValue(double tx, double ty, double th) {
  double a = DEG2RAD(th);

  double error=0;
  int pn=0;
  int nn=0;
  for (size_t i=0; i<curLps.size(); i++) {
    const LPoint2D *clp = curLps[i];             // ���݃X�L�����̓_
    const LPoint2D *rlp = refLps[i];             // clp�ɑΉ�����Q�ƃX�L�����̓_

    if (rlp->type != LINE)                       // ������̓_�łȂ���Ύg��Ȃ�
      continue;
 
    double cx = clp->x;
    double cy = clp->y;
    double x = cos(a)*cx - sin(a)*cy + tx;       // clp���Q�ƃX�L�����̍��W�n�ɕϊ�
    double y = sin(a)*cx + cos(a)*cy + ty;

    double pdis = (x - rlp->x)*rlp->nx + (y - rlp->y)*rlp->ny;         // ��������

    double er = pdis*pdis;
    if (er <= evlimit*evlimit)
      ++pn;                                      // �덷���������_�̐�

    error += er;                                 // �e�_�̌덷��ݐ�
    ++nn;
  }

  error = (nn>0)? error/nn : HUGE_VAL;           // �L���_����0�Ȃ�A�l��HUGE_VAL
  pnrate = 1.0*pn/nn;                            // �덷���������_�̔䗦

//  printf("CostFunctionPD: error=%g, pnrate=%g, evlimit=%g\n", error, pnrate, evlimit);     // �m�F�p

  error *= 100;                                  // �]���l���������Ȃ肷���Ȃ��悤100������B

  return(error);
}
