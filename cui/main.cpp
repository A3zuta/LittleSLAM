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
 * @file main.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "SlamLauncher.h"

int main(int argc, char *argv[]) {
  bool scanCheck=false;              // �X�L�����\���݂̂�
  bool odometryOnly=false;           // �I�h���g���ɂ��n�}�\�z��
  char *filename;                    // �f�[�^�t�@�C����
  int startN=0;                      // �J�n�X�L�����ԍ�

  if (argc < 2) {
    printf("Error: too few arguments.\n");
    return(1);
  }

  // �R�}���h�����̏���
  int idx=1;
  // �R�}���h�I�v�V�����̉��߁i'-'�̂��������j
  if (argv[1][0] == '-') {
    for (int i=1; ; i++) {
      char option = argv[1][i];
      if (option == NULL)
        break;
      else if (option == 's')        // �X�L�����\���̂�
        scanCheck = true;
      else if (option == 'o')        // �I�h���g���ɂ��n�}�\�z
        odometryOnly = true;
    }
    if (argc == 2) {
      printf("Error: no file name.\n");
      return(1);
    }
    ++idx;
  }
  if (argc >= idx+1)                 // '-'����ꍇidx=2�A�Ȃ��ꍇidx=1
    filename = argv[idx];
  if (argc == idx+2)                 // argc��idx���2�傫�����startN������
    startN = atoi(argv[idx+1]);
  else if (argc >= idx+2) {
    printf("Error: invalid arguments.\n");
    return(1);
  }
  
  printf("SlamLauncher: startN=%d, scanCheck=%d, odometryOnly=%d\n", startN, scanCheck, odometryOnly);
  printf("filename=%s\n", filename);

  // �t�@�C�����J��
  SlamLauncher sl;
  bool flag = sl.setFilename(filename);
  if (!flag)
    return(1);

  sl.setStartN(startN);              // �J�n�X�L�����ԍ��̐ݒ�

  // �����{��
  if (scanCheck)
    sl.showScans();
  else {                             // �X�L�����\���ȊO��SlamLauncher���ŏꍇ����
    sl.setOdometryOnly(odometryOnly);
    sl.customizeFramework();
    sl.run();
  }

  return(0);
}
