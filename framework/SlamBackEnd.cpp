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
 * @file SlamBackEnd.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "SlamBackEnd.h"
#include "P2oDriver2D.h"

using namespace std;

////////// �|�[�Y���� //////////

Pose2D SlamBackEnd::adjustPoses() {
//  pg->printArcs();
//  pg->printNodes();

  newPoses.clear();

  P2oDriver2D p2o;
  p2o.doP2o(*pg, newPoses, 5);                 // 5�񂭂�Ԃ�

  return(newPoses.back());
}

/////////////////////////////

void SlamBackEnd::remakeMaps() {
  // PoseGraph�̏C��
  vector<PoseNode*> &pnodes = pg->nodes;      // �|�[�Y�m�[�h
  for (size_t i=0; i<newPoses.size(); i++) {
    Pose2D &npose = newPoses[i];
    PoseNode *pnode = pnodes[i];              // �m�[�h�̓��{�b�g�ʒu��1:1�Ή�
    pnode->setPose(npose);                    // �e�m�[�h�̈ʒu���X�V
  }
  printf("newPoses.size=%lu, nodes.size=%lu\n", newPoses.size(), pnodes.size());

  // PointCloudMap�̏C��
  pcmap->remakeMaps(newPoses);
}
