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
 * @file SlamFrontEnd.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "SlamFrontEnd.h"

using namespace std;

/////////

// ������
void SlamFrontEnd::init() {
  smat->reset();
  smat->setPointCloudMap(pcmap);
  sback.setPointCloudMap(pcmap);
}

///////////

// ���݃X�L����scan����������B
void SlamFrontEnd::process(Scan2D &scan) {
  if (cnt == 0) 
    init();                                       // �J�n���ɏ�����

  // �X�L�����}�b�`���O
  smat->matchScan(scan);

  Pose2D curPose = pcmap->getLastPose();          // ����̓X�L�����}�b�`���O�Ő��肵�����݂̃��{�b�g�ʒu
  
  // �|�[�Y�O���t�ɃI�h���g���A�[�N��ǉ�
  if (cnt == 0) {                                 // �ŏ��̓m�[�h��u�������B
    pg->addNode(curPose);
  }
  else {                                          // ������̓m�[�h��ǉ����āA�I�h���g���A�[�N�𒣂�
    Eigen::Matrix3d &cov = smat->getCovariance();
    makeOdometryArc(curPose, cov);
  }

  if (cnt%keyframeSkip==0) {                             // �L�[�t���[���̂Ƃ������s��
    if (cnt == 0)
      pcmap->setNthre(1);                                // cnt=0�̂Ƃ��͒n�}���������̂ŃT���v�����O��������
    else
      pcmap->setNthre(5);
    pcmap->makeGlobalMap();                              // �_�Q�n�}�̑S�̒n�}�𐶐�
  }

  // ���[�v������
  if (cnt > keyframeSkip && cnt%keyframeSkip==0) {       // �L�[�t���[���̂Ƃ������s��
    bool flag = lpd->detectLoop(&scan, curPose, cnt);    // ���[�v���o���N��
    if (flag) {
      sback.adjustPoses();                               // ���[�v������������|�[�Y����
      sback.remakeMaps();                                // �n�}��|�[�Y�O���t�̏C��
    }
  }

  printf("pcmap.size=%lu\n", pcmap->globalMap.size());   // �m�F�p

  countLoopArcs();            // �m�F�p

  ++cnt;
}

////////////

// �I�h���g���A�[�N�̐���
bool SlamFrontEnd::makeOdometryArc(Pose2D &curPose, const Eigen::Matrix3d &fusedCov) {
  if (pg->nodes.size() == 0)                             // �O�̂��߂̃`�F�b�N
    return(false);
  PoseNode *lastNode = pg->nodes.back();                 // ���O�m�[�h
  PoseNode *curNode = pg->addNode(curPose);              // �|�[�Y�O���t�Ɍ��݃m�[�h��ǉ�

  // ���O�m�[�h�ƌ��݃m�[�h�̊ԂɃI�h���g���A�[�N�𒣂�
  Pose2D &lastPose = lastNode->pose;
  Pose2D relPose;
  Pose2D::calRelativePose(curPose, lastPose, relPose);   // ���݈ʒu�ƒ��O�ʒu�̑��Έʒu�i�ړ��ʁj�̌v�Z
  printf("sfront: lastPose:  tx=%g, ty=%g, th=%g\n", lastPose.tx, lastPose.ty, lastPose.th);

  Eigen::Matrix3d cov;
  CovarianceCalculator::rotateCovariance(lastPose, fusedCov, cov, true);     // �ړ��ʂ̋����U�ɕϊ�
  PoseArc *arc = pg->makeArc(lastNode->nid, curNode->nid, relPose, cov);     // �A�[�N�̐���
  pg->addArc(arc);                                                           // �|�[�Y�O���t�ɃA�[�N��ǉ�

  return(true);
}

////////////

// ���[�v�A�[�N���𐔂���B�m�F�p
void SlamFrontEnd::countLoopArcs() {
  vector<PoseArc*> &parcs = pg->arcs;       // �S�|�[�Y�A�[�N
  int an=0;                                 // ���[�v�A�[�N��
  for (size_t i=0; i<parcs.size(); i++) {
    PoseArc *a = parcs[i];
    PoseNode *src = a->src;
    PoseNode *dst = a->dst;
    if (src->nid != dst->nid-1)             // �I�h���g���A�[�N�͎n�_�ƏI�_���A�ԂɂȂ��Ă���
      ++an;                                 // �I�h���g���A�[�N�łȂ���΃��[�v�A�[�N
  }
  printf("loopArcs.size=%d\n", an);         // �m�F�p
}
