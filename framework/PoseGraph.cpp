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
 * @file PoseGraph.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "PoseGraph.h"

using namespace std;

//////////// �O���t���� ////////////

// �|�[�Y�O���t�Ƀm�[�h�ǉ�
PoseNode *PoseGraph::addNode(const Pose2D &pose) {
  PoseNode *n1 = allocNode();                // �m�[�h����
  addNode(n1, pose);                         // �|�[�Y�O���t�Ƀm�[�h�ǉ�

  return(n1);
}

// �|�[�Y�O���t�Ƀm�[�h�ǉ�
void PoseGraph::addNode(PoseNode *n1, const Pose2D &pose) {
  n1->setNid((int)nodes.size());             // �m�[�hID�t�^�B�m�[�h�̒ʂ��ԍ��Ɠ���
  n1->setPose(pose);                         // ���{�b�g�ʒu��ݒ�
  nodes.push_back(n1);                       // nodes�̍Ō�ɒǉ�
}

// �m�[�hID(nid)����m�[�h���̂�������
PoseNode *PoseGraph::findNode(int nid) {
  for (size_t i=0; i<nodes.size(); i++) {    // �P���ɐ��`�T��
    PoseNode *n = nodes[i];
    if (n->nid == nid)                       // nid����v�����猩����
      return(n);
  }

  return(nullptr);
}

//////////

// �|�[�Y�O���t�ɃA�[�N��ǉ�����
void PoseGraph::addArc(PoseArc *arc) {
  arc->src->addArc(arc);                   // �n�_�m�[�h��arc��ǉ�
  arc->dst->addArc(arc);                   // �I�_�m�[�h��arc��ǉ�
  arcs.push_back(arc);                     // arcs�̍Ō��arc��ǉ�
}

// �n�_�m�[�hsrcNid�ƏI�_�m�[�hdstNid�̊ԂɃA�[�N�𐶐�����
PoseArc *PoseGraph::makeArc(int srcNid, int dstNid, const Pose2D &relPose, const Eigen::Matrix3d &cov) {
//  Eigen::Matrix3d inf = cov.inverse();         // inf��cov�̋t�s��
  Eigen::Matrix3d inf = MyUtil::svdInverse(cov);            // inf��cov�̋t�s��

  PoseNode *src = nodes[srcNid];                // �n�_�m�[�h
  PoseNode *dst = nodes[dstNid];                // �I�_�m�[�h

  PoseArc *arc = allocArc();                    // �A�[�N�̐���
  arc->setup(src, dst, relPose, inf);      // relPose�͌v���ɂ�鑊�Έʒu

  return(arc);
}

// �n�_�m�[�h��srcNid�A�I�_�m�[�h��dstNid�ł���A�[�N��Ԃ�
PoseArc *PoseGraph::findArc(int srcNid, int dstNid) {
  for (size_t i=0; i<arcs.size(); i++) {
    PoseArc *a = arcs[i];
    if (a->src->nid == srcNid && a->dst->nid == dstNid)
      return(a);
  }
  return(nullptr);
}

////////////////

// �m�F�p
void PoseGraph::printNodes() {
  printf("--- printNodes ---\n");
  printf("nodes.size=%lu\n", nodes.size());
  for (size_t i=0; i<nodes.size(); i++) {
    PoseNode *node = nodes[i];
    printf("i=%lu: nid=%d, tx=%g, ty=%g, th=%g\n", i, node->nid, node->pose.tx, node->pose.ty, node->pose.th);

    for (size_t j=0; j<node->arcs.size(); j++) {
      PoseArc *a = node->arcs[j];
      printf("arc j=%lu: srcId=%d, dstId=%d, src=%p, dst=%p\n", j, a->src->nid, a->dst->nid, a->src, a->dst);
    }
  }
}

// �m�F�p
void PoseGraph::printArcs() {
  printf("--- printArcs ---\n");
  printf("arcs.size=%lu\n", arcs.size());
  for (size_t j=0; j<arcs.size(); j++) {
    PoseArc *a = arcs[j];
    double dis = (a->src->pose.tx - a->dst->pose.tx)*(a->src->pose.tx - a->dst->pose.tx) + (a->src->pose.ty - a->dst->pose.ty)*(a->src->pose.ty - a->dst->pose.ty);

    Pose2D &rpose = a->relPose;
    printf("j=%lu, srcId=%d, dstId=%d, tx=%g, ty=%g, th=%g\n", j, a->src->nid, a->dst->nid, rpose.tx, rpose.ty, rpose.th);
  }
}
