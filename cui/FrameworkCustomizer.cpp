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
 * @file FrameworkCustomizer.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "FrameworkCustomizer.h"

using namespace std;

// �t���[�����[�N�̊�{������ݒ�
void FrameworkCustomizer::makeFramework() {
  smat.setPoseEstimator(&poest);
  smat.setPoseFuser(&pfu);

  // LoopDetectorSS�͎g�����i�����܂��Ă���̂ŁA�����œ����
  lpdSS.setPoseEstimator(&poest);
  lpdSS.setPoseFuser(&pfu);
  lpdSS.setDataAssociator(&dassGT);
  lpdSS.setCostFunction(&cfuncPD);
  lpdSS.setPointCloudMap(&pcmapLP);

  sfront->setScanMatcher(&smat);
}

/////// �����p

// �t���[�����[�N��{�\��
void FrameworkCustomizer::customizeA() {
  pcmap = &pcmapBS;                                // �S�X�L�����_��ۑ�����_�Q�n�}
  RefScanMaker *rsm = &rsmBS;                      // ���O�X�L�������Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassLS;                  // ���`�T���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncED;                  // ���[�N���b�h�������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSD;                   // �ŋ}�~���@�ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �i�q�e�[�u���̗��p
void FrameworkCustomizer::customizeB() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassLS;                  // ���`�T���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncED;                  // ���[�N���b�h�������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSD;                   // �ŋ}�~���@�ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �ŋ}�~���@�̌�ɒ����T�����s��
void FrameworkCustomizer::customizeC() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassLS;                  // ���`�T���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncED;                  // ���[�N���b�h�������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �f�[�^�Ή��Â����i�q�e�[�u���ōs��
void FrameworkCustomizer::customizeD() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncED;                  // ���[�N���b�h�������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �X�L�����_�Ԋu�ψꉻ��ǉ�
void FrameworkCustomizer::customizeE() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncED;                  // ���[�N���b�h�������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);              // �X�L�����_�Ԋu�ψꉻ
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �X�L�����_�̖@���v�Z��ǉ�
void FrameworkCustomizer::customizeF() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncPD;                  // �����������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointAnalyser(&spana);               // �X�L�����_�̖@���v�Z
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �X�L�����_�Ԋu�ψꉻ�Ɩ@���v�Z��ǉ�
void FrameworkCustomizer::customizeG() {
  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncPD;                  // �����������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);              // �X�L�����_�Ԋu�ψꉻ
  smat.setScanPointAnalyser(&spana);               // �X�L�����_�̖@���v�Z
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // �Z���T�Z�����Ȃ�
}

// �Z���T�Z����ǉ�
void FrameworkCustomizer::customizeH() {
//  pcmap = &pcmapGT;                                // �i�q�e�[�u���ŊǗ�����_�Q�n�}
  pcmap = &pcmapLP;                                // �����n�}���ƂɊǗ�����_�Q�n�}�BcI�Ƃ̔�r�p
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncPD;                  // �����������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdDM;                      // �_�~�[�̃��[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);
  smat.setScanPointAnalyser(&spana);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(true);                        // �Z���T�Z������
}

// �Z���T�Z���ƃ��[�v�����݂�ǉ�
void FrameworkCustomizer::customizeI() {
  pcmap = &pcmapLP;                                // �����n�}���ƂɊǗ�����_�Q�n�}
  RefScanMaker *rsm = &rsmLM;                      // �Ǐ��n�}���Q�ƃX�L�����Ƃ���
  DataAssociator *dass = &dassGT;                  // �i�q�e�[�u���ɂ��f�[�^�Ή��Â�
  CostFunction *cfunc = &cfuncPD;                  // �����������R�X�g�֐��Ƃ���
  PoseOptimizer *popt = &poptSL;                   // �ŋ}�~���@�ƒ����T���ɂ��œK��
  LoopDetector *lpd = &lpdSS;                      // �����n�}��p�������[�v���o

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);
  smat.setScanPointAnalyser(&spana);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(true);                        // �Z���T�Z������
}
