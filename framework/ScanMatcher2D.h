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
 * @file ScanMatcher2D.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef SCAN_MATCHER2D_H_
#define SCAN_MATCHER2D_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"
#include "PointCloudMap.h"
#include "RefScanMaker.h"
#include "ScanPointResampler.h"
#include "ScanPointAnalyser.h"
#include "PoseEstimatorICP.h"
#include "PoseFuser.h"

// ICP��p���ăX�L�����}�b�`���O���s��
class ScanMatcher2D
{
private:
  int cnt;                                // �_�������B�X�L�����ԍ��ɑΉ�
  Scan2D prevScan;                        // 1�O�̃X�L����
  Pose2D initPose;                        // �n�}�̌��_�̈ʒu�B�ʏ�(0,0,0)

  double scthre;                          // �X�R�A臒l�B������傫����ICP���s�Ƃ݂Ȃ�
  double nthre;                           // �g�p�_��臒l�B�����菬������ICP���s�Ƃ݂Ȃ�
  double atd;                             // �ݐϑ��s�����B�m�F�p
  bool dgcheck;                           // �މ����������邩

  PoseEstimatorICP *estim;                // ���{�b�g�ʒu�����
  PointCloudMap *pcmap;                   // �_�Q�n�}
  ScanPointResampler *spres;              // �X�L�����_�Ԋu�ψꉻ
  ScanPointAnalyser *spana;               // �X�L�����_�@���v�Z
  RefScanMaker *rsm;                      // �Q�ƃX�L��������
  PoseFuser *pfu;                         // �Z���T�Z����
  Eigen::Matrix3d cov;                    // ���{�b�g�ړ��ʂ̋����U�s��
  Eigen::Matrix3d totalCov;               // ���{�b�g�ʒu�̋����U�s��

  std::vector<PoseCov> poseCovs;          // �f�o�b�O�p

public:
  ScanMatcher2D() : cnt(-1), scthre(1.0), nthre(50), dgcheck(false), atd(0), pcmap(nullptr), spres(nullptr), spana(nullptr), estim(nullptr), rsm(nullptr), pfu(nullptr) {
  }

  ~ScanMatcher2D() {
  }

/////// �t���[�����[�N�̉����ӏ� ////////

  void setPoseEstimator(PoseEstimatorICP *p) {
    estim = p;
  }

  void setPoseFuser(PoseFuser *p) {
    pfu = p;
  }

  void setScanPointResampler(ScanPointResampler *s) {
    spres = s;
  }

  void setScanPointAnalyser(ScanPointAnalyser *s) {
    spana = s;
  }

   void setRefScanMaker(RefScanMaker *r) {
     rsm = r;
     if (pcmap != nullptr)
       rsm->setPointCloudMap(pcmap);
   }
   
  void setPointCloudMap(PointCloudMap *m) {
    pcmap = m;
    if (rsm != nullptr)
      rsm->setPointCloudMap(pcmap);
  }

///////

  void reset() {
    cnt = -1;
  }

  void setInitPose(Pose2D &p) {
    initPose = p;
  }

  void setDgCheck(bool t) {
    dgcheck = t;
  }

  Eigen::Matrix3d &getCovariance() {
    return(cov);
  }

  // �f�o�b�O�p
  std::vector<PoseCov> &getPoseCovs() {
    return(poseCovs);
  }
  
//////////

  bool matchScan(Scan2D &scan);
  void growMap(const Scan2D &scan, const Pose2D &pose);

};

#endif
