## �v���O�����̃J�X�^�}�C�Y

LittleSLAM�́A�傫���A�X�L�����}�b�`���O�A�Z���T�Z���A���[�v�����݂Ƃ���
�v�f�Z�p����\������Ă��܂��B
LittleSLAM�́A�w�K�p�v���O�����Ƃ��āA�����̋Z�p�Ɋւ���
�������̃J�X�^�}�C�Y���ł���悤�ɍ���Ă��܂��B
���\�ɃJ�X�^�}�C�Y�̃^�C�v�������܂��B
���ꂼ��̏ڍׂ́A�Q�l����[1]���Q�Ƃ��Ă��������B


| �^�C�v              | ���e         |
|:--------------------|:-------------|
| customizeA          | �X�L�����}�b�`���O��{�`  |
| customizeB          | �X�L�����}�b�`���O���ǌ`1 |
| customizeC          | �X�L�����}�b�`���O���ǌ`2 |
| customizeD          | �X�L�����}�b�`���O���ǌ`3 | 
| customizeE          | �X�L�����}�b�`���O���ǌ`4 |
| customizeF          | �X�L�����}�b�`���O���ǌ`5 | 
| customizeG          | �X�L�����}�b�`���O���ǌ`6 | 
| customizeH          | �Z���T�Z���ɂ��މ��̑Ώ� |
| customizeI          | ���[�v������ |


�J�X�^�}�C�Y�̃^�C�v�́ASlamLauncher.cpp��
�֐�customizeFramework�̒��ŁA���L�̂悤�Ɏw�肵�܂��B
�\�̃^�C�v�����̂܂܊֐����ł���A�w�肵�����֐��������āA
����ȊO�̓R�����g�A�E�g���܂��B  
�f�t�H���g�́AcustomizeI�ɂȂ��Ă��܂��B

```C++

void SlamLauncher::customizeFramework() {
  fcustom.setSlamFrontEnd(&sfront);
  fcustom.makeFramework();
//  fcustom.customizeG();                   // �g��Ȃ��̂ŃR�����g�A�E�g
  fcustom.customizeI();                     // ���̃J�X�^�}�C�Y���w��

  pcmap = fcustom.getPointCloudMap();
}

```  

�܂��A�֐�customizeX�iX=A to I�j�́Acui/FrameworkCustomizer.cpp�Œ�`����Ă��܂��B  
���[�U���V����customizeX������Ď������Ƃ��\�ł��B


