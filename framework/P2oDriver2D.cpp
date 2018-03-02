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
 * @file P2oDriver2D.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "P2oDriver2D.h"
#include "p2o.h"

using namespace std;

////////

// kslam��p���ă|�[�Y�O���tpg���|�[�Y�������A���̌��ʂ̃��{�b�g�O�Ղ�newPoses�Ɋi�[����B
void P2oDriver2D::doP2o( PoseGraph &pg, vector<Pose2D> &newPoses, int N) {
  vector<PoseNode*> &nodes = pg.nodes;                        // �|�[�Y�m�[�h
  vector<PoseArc*> &arcs = pg.arcs;                           // �|�[�Y�A�[�N

  // �|�[�Y�m�[�h��p2o�p�ɕϊ�
  vector<p2o::Pose2D> pnodes;                                  // p2o�̃|�[�Y�m�[�h�W��
  for (size_t i=0; i<nodes.size(); i++) {
    PoseNode *node = nodes[i];
    Pose2D pose = node->pose;                                  // �m�[�h�̈ʒu
    pnodes.push_back(p2o::Pose2D(pose.tx, pose.ty, DEG2RAD(pose.th)));   // �ʒu���������
  }


  // �|�[�Y�A�[�N��kslam�p�ɕϊ�
  p2o::Con2DVec pcons;                             // p2o�̃|�[�Y�A�[�N�W��
  for (size_t i=0; i<arcs.size(); i++) {
    PoseArc *arc = arcs[i];
    PoseNode *src = arc->src;
    PoseNode *dst = arc->dst;
    Pose2D &relPose = arc->relPose;
    p2o::Con2D con;
    con.id1 = src->nid;
    con.id2 = dst->nid;
    con.t = p2o::Pose2D(relPose.tx, relPose.ty, DEG2RAD(relPose.th));
    for (int k=0; k<3; k++)
      for (int m=0; m<3; m++)
        con.info(k, m) = arc->inf(k,m);
    pcons.push_back(con);
  }

//  printf("knodes.size=%lu, kcons.size=%lu\n", knodes.size(), kcons.size());    // �m�F�p

  p2o::Optimizer2D opt;                                          // p2o�C���X�^���X
  std::vector<p2o::Pose2D> result = opt.optimizePath(pnodes, pcons, N);  // N����s

   // ���ʂ�newPose�Ɋi�[����
  for (size_t i=0; i<result.size(); i++) {
    p2o::Pose2D newPose = result[i];                                      // i�Ԗڂ̃m�[�h�̏C�����ꂽ�ʒu
    Pose2D pose(newPose.x, newPose.y, RAD2DEG(newPose.th));
    newPoses.emplace_back(pose);
  }
}
