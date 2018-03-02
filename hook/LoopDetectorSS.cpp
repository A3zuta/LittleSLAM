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
 * @file LoopDetectorSS.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "LoopDetectorSS.h"

using namespace std;

////////////

// ���[�v���o
// ���݈ʒucurPose�ɋ߂��A���݃X�L����curScan�Ɍ`����v����ꏊ�����{�b�g�O�Ղ��猩���ă|�[�Y�A�[�N�𒣂�B
bool LoopDetectorSS::detectLoop(Scan2D *curScan, Pose2D &curPose, int cnt) {
  printf("-- detectLoop -- \n");

  // �ł��߂������n�}��T��
  double atd = pcmap->atd;                             // ���݂̎��ۂ̗ݐϑ��s����
  double atdR = 0;                                     // ���L�̏����ŋO�Ղ��Ȃ��鎞�̗ݐϑ��s����
  const vector<Submap> &submaps = pcmap->submaps;      // �����n�}
  const vector<Pose2D> &poses = pcmap->poses;          // ���{�b�g�O��
  double dmin=HUGE_VAL;                                // �O��K��_�܂ł̋����̍ŏ��l
  size_t imin=0, jmin=0;                               // �����ŏ��̑O��K��_�̃C���f�b�N�X
  Pose2D prevP;                                        // ���O�̃��{�b�g�ʒu
  for (size_t i=0; i<submaps.size()-1; i++) {          // ���݂̕����n�}�ȊO��T��
    const Submap &submap = submaps[i];                 // i�Ԗڂ̕����n�}
    for (size_t j=submap.cntS; j<=submap.cntE; j++) {  // �����n�}�̊e���{�b�g�ʒu�ɂ���
      Pose2D p = poses[j];                             // ���{�b�g�ʒu
      atdR += sqrt((p.tx - prevP.tx)*(p.tx - prevP.tx) + (p.ty - prevP.ty)*(p.ty - prevP.ty));
      if (atd-atdR < atdthre) {                        // ���݈ʒu�܂ł̑��s�������Z���ƃ��[�v�Ƃ݂Ȃ����A������߂�
        i = submaps.size();                            // ����ŊO���̃��[�v�����������
        break;
      }
      prevP = p;

      double d = (curPose.tx - p.tx)*(curPose.tx - p.tx) + (curPose.ty - p.ty)*(curPose.ty - p.ty);
      if (d < dmin) {                                  // ���݈ʒu��p�Ƃ̋���������܂ł̍ŏ���
        dmin = d;
        imin = i;                                      // ���ƂȂ镔���n�}�̃C���f�b�N�X
        jmin = j;                                      // �O��K��_�̃C���f�b�N�X
      }
//      printf("i=%lu, j=%lu: atd=%g, atdR=%g, atdthre=%g\n", i, j, atd, atdR, atdthre);             // �m�F�p
    }
  }

  printf("dmin=%g, radius=%g, imin=%lu, jmin=%lu\n", sqrt(dmin), radius, imin, jmin);  // �m�F�p

  if (dmin > radius*radius)                            // �O��K��_�܂ł̋����������ƃ��[�v���o���Ȃ�
    return(false);

  Submap &refSubmap = pcmap->submaps[imin];            // �ł��߂������n�}���Q�ƃX�L�����ɂ���
  const Pose2D &initPose = poses[jmin];
  printf("curPose:  tx=%g, ty=%g, th=%g\n", curPose.tx, curPose.ty, curPose.th);
  printf("initPose: tx=%g, ty=%g, th=%g\n", initPose.tx, initPose.ty, initPose.th);

  // �ĖK�_�̈ʒu�����߂�
  Pose2D revisitPose;
  bool flag = estimateRevisitPose(curScan, refSubmap.mps, curPose, revisitPose);
//  bool flag = estimateRelativePose(curScan, refSubmap.mps, initPose, revisitPose);

  if (flag) {                                          // ���[�v�����o����
    Eigen::Matrix3d icpCov;                                                  // ICP�̋����U
    double ratio = pfu->calIcpCovariance(revisitPose, curScan, icpCov);      // ICP�̋����U���v�Z

    LoopInfo info;                                     // ���[�v���o����
    info.pose = revisitPose;                           // ���[�v�A�[�N���ɍĖK�_�ʒu��ݒ�
    info.cov = icpCov;                                 // ���[�v�A�[�N���ɋ����U��ݒ�B
    info.curId = cnt;                                  // ���݈ʒu�̃m�[�hid
    info.refId = static_cast<int>(jmin);               // �O��K��_�̃m�[�hid
    makeLoopArc(info);                                 // ���[�v�A�[�N����

    // �m�F�p
    Scan2D refScan;
    Pose2D spose = poses[refSubmap.cntS];
    refScan.setSid(info.refId);
    refScan.setLps(refSubmap.mps);
    refScan.setPose(spose);
    LoopMatch lm(*curScan, refScan, info);
    loopMatches.emplace_back(lm);
    printf("curId=%d, refId=%d\n", info.curId, info.refId);
  }

  return(flag);
}

//////////

// �O��K��_(refId)���n�_�m�[�h�A���݈ʒu(curId)���I�_�m�[�h�ɂ��āA���[�v�A�[�N�𐶐�����B
void LoopDetectorSS::makeLoopArc(LoopInfo &info) {
  if (info.arcked)                                             // info�̃A�[�N�͂��łɒ����Ă���
    return;
  info.setArcked(true);

  Pose2D srcPose = pcmap->poses[info.refId];                   // �O��K��_�̈ʒu
  Pose2D dstPose(info.pose.tx, info.pose.ty, info.pose.th);    // �ĖK�_�̈ʒu
  Pose2D relPose;
  Pose2D::calRelativePose(dstPose, srcPose, relPose);          // ���[�v�A�[�N�̍S��

  // �A�[�N�̍S���͎n�_�m�[�h����̑��Έʒu�Ȃ̂ŁA�����U�����[�v�A�[�N�̎n�_�m�[�h���W�n�ɕϊ�
  Eigen::Matrix3d cov;
  CovarianceCalculator::rotateCovariance(srcPose, info.cov, cov, true);    // �����U�̋t��]

  PoseArc *arc = pg->makeArc(info.refId, info.curId, relPose, cov);        // ���[�v�A�[�N����
  pg->addArc(arc);                                                         // ���[�v�A�[�N�o�^

  // �m�F�p
  printf("makeLoopArc: pose arc added\n");
  printf("srcPose: tx=%g, ty=%g, th=%g\n", srcPose.tx, srcPose.ty, srcPose.th);
  printf("dstPose: tx=%g, ty=%g, th=%g\n", dstPose.tx, dstPose.ty, dstPose.th);
  printf("relPose: tx=%g, ty=%g, th=%g\n", relPose.tx, relPose.ty, relPose.th);
  PoseNode *src = pg->findNode(info.refId);
  PoseNode *dst = pg->findNode(info.curId);
  Pose2D relPose2;
  Pose2D::calRelativePose(dst->pose, src->pose, relPose2);
  printf("relPose2: tx=%g, ty=%g, th=%g\n", relPose2.tx, relPose2.ty, relPose2.th);
}

//////////

// ���݃X�L����curScan�ƕ����n�}�̓_�QrefLps��ICP���s���A�ĖK�_�̈ʒu�����߂�B
bool LoopDetectorSS::estimateRevisitPose(const Scan2D *curScan, const vector<LPoint2D> &refLps, const Pose2D &initPose, Pose2D &revisitPose) {
  dass->setRefBase(refLps);                              // �f�[�^�Ή��Â���ɎQ�Ɠ_�Q��ݒ�
  cfunc->setEvlimit(0.2);                                // �R�X�g�֐��̌덷臒l

  printf("initPose: tx=%g, ty=%g, th=%g\n", initPose.tx, initPose.ty, initPose.th);       // �m�F�p

  size_t usedNumMin = 50; 
//  size_t usedNumMin = 100;

  // �����ʒuinitPose�̎��͂�����݂Ԃ��ɒ��ׂ�B
  // �������̂��߁AICP�͍s�킸�A�e�ʒu�ŒP���Ƀ}�b�`���O�X�R�A�𒲂ׂ�B
  double rangeT = 1;                                     // ���i�̒T���͈�[m]
  double rangeA = 45;                                    // ��]�̒T���͈�[�x]
  double dd = 0.2;                                       // ���i�̒T���Ԋu[m]
  double da = 2;                                         // ��]�̒T���Ԋu[�x]
  double pnrateMax=0;
  vector<double> pnrates;
  double scoreMin=1000;
  vector<double> scores;
  vector<Pose2D> candidates;                             // �X�R�A�̂悢���ʒu
  for (double dy=-rangeT; dy<=rangeT; dy+=dd) {          // ���iy�̒T���J��Ԃ�
    double y = initPose.ty + dy;                         // �����ʒu�ɕψʕ�dy��������
    for (double dx=-rangeT; dx<=rangeT; dx+=dd) {        // ���ix�̒T���J��Ԃ�
      double x = initPose.tx + dx;                       // �����ʒu�ɕψʕ�dx��������
      for (double dth=-rangeA; dth<=rangeA; dth+=da) {   // ��]�̒T���J��Ԃ�
        double th = MyUtil::add(initPose.th, dth);       // �����ʒu�ɕψʕ�dth��������
        Pose2D pose(x, y, th);
        double mratio = dass->findCorrespondence(curScan, pose);   // �ʒupose�Ńf�[�^�Ή��Â�
        size_t usedNum = dass->curLps.size();
//        printf("usedNum=%lu, mratio=%g\n", usedNum, mratio);          // �m�F�p
        if (usedNum < usedNumMin || mratio < 0.9)        // �Ή����������Ɣ�΂�
          continue;
        cfunc->setPoints(dass->curLps, dass->refLps);    // �R�X�g�֐��ɓ_�Q��ݒ�
        double score =  cfunc->calValue(x, y, th);       // �R�X�g�l�i�}�b�`���O�X�R�A�j
        double pnrate = cfunc->getPnrate();              // �ڍׂȓ_�̑Ή���
//        printf("score=%g, pnrate=%g\n", score, pnrate);                    // �m�F�p
        if (pnrate > 0.8) {
          candidates.emplace_back(pose);
          if (score < scoreMin)
            scoreMin = score;
          scores.push_back(score);
//          printf("pose: tx=%g, ty=%g, th=%g\n", pose.tx, pose.ty, pose.th);  // �m�F�p
//          printf("score=%g, pnrate=%g\n", score, pnrate);                    // �m�F�p
        }
      }
    }
  }
  printf("candidates.size=%lu\n", candidates.size());                           // �m�F�p
  if (candidates.size() == 0)
    return(false);

  // ���ʒucandidates�̒�����ł��悢���̂�ICP�őI��
  Pose2D best;                                              // �ŗǌ��
  double smin=1000000;                                      // ICP�X�R�A�ŏ��l
  estim->setScanPair(curScan, refLps);                      // ICP�ɃX�L�����ݒ�
  for (size_t i=0; i<candidates.size(); i++) {
    Pose2D p = candidates[i];                               // ���ʒu
    printf("score=%g\n", scores[i]);    // �m�F�p
    Pose2D estP;
    double score = estim->estimatePose(p, estP);            // ICP�Ń}�b�`���O�ʒu�����߂�
    double pnrate = estim->getPnrate();                     // ICP�ł̓_�̑Ή���
    size_t usedNum = estim->getUsedNum();                   // ICP�Ŏg�p�����_��
    if (score < smin && pnrate >= 0.9 && usedNum >= usedNumMin) {  // ���[�v���o�͏���������
      smin = score;
      best = estP;
      printf("smin=%g, pnrate=%g, usedNum=%lu\n", smin, pnrate, usedNum);    // �m�F�p
    }
  }

  // �ŏ��X�R�A��臒l��菬������Ό�����
  if (smin <= scthre) {
    revisitPose = best;
    return(true);
  }

  return(false);
}
