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
 * @file RefScanMakerBS.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "RefScanMakerBS.h"

using namespace std;

const Scan2D *RefScanMakerBS::makeRefScan() {
  vector<LPoint2D> &refLps = refScan.lps;         // �Q�ƃX�L�����̓_�Q�̃R���e�i
  refLps.clear();

  Pose2D lastPose = pcmap->getLastPose();         // �_�Q�n�}�ɕۑ������Ō�̐���ʒu
  double (*R)[2] = lastPose.Rmat;
  double tx = lastPose.tx;
  double ty = lastPose.ty;

  // �_�Q�n�}�ɕۑ������Ō�̃X�L�������Q�ƃX�L�����ɂ���
  const vector<LPoint2D> &lps = pcmap->lastScan.lps;
  for (size_t i=0; i<lps.size(); i++) {
    const LPoint2D &mp = lps[i];                  // �Q�ƃX�L�����̓_

    // �X�L�����̓��{�b�g���W�n�Ȃ̂ŁA�n�}���W�n�ɕϊ�
    LPoint2D rp;
    rp.x = R[0][0]*mp.x + R[0][1]*mp.y + tx;      // �_�̈ʒu
    rp.y = R[1][0]*mp.x + R[1][1]*mp.y + ty;
    rp.nx = R[0][0]*mp.nx + R[0][1]*mp.ny;        // �@���x�N�g��
    rp.ny = R[1][0]*mp.nx + R[1][1]*mp.ny;
    refLps.emplace_back(rp);
  }

  return(&refScan);
}
