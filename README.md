# BFM模型可视化工具 - C++
通过C++和Qt5构建的一个Basel人脸模型（Basel Face Model, BFM）的可视化工具。

<img src="https://github.com/Great-Keith/bfm-visual-tool/raw/master/assets/avg_v1.1.png" width="80%">



## 数据准备

下载好BFM模型（2009年版本的01_MorphableModel.mat文件）后，通过Matlab脚本（提供于./matlab_utils目录下）将其转换成二进制文件用于读写。

```
function bfm_mat2binary(bfm_model)
    load(bfm_model)
    mat2binary('shapeEV.bin', shapeEV, 'single')
    mat2binary('shapeMU.bin', shapeMU, 'single')
    mat2binary('shapePC.bin', shapePC, 'single')
    mat2binary('texEV.bin', texEV, 'single')
    mat2binary('texMU.bin', texMU, 'single')
    mat2binary('texPC.bin', texPC, 'single')
    mat2binary('tl.bin', tl, 'double')
end
```

将这些生成文件放置于目录./data下。

或者可以直接下载Release页面中的data.zip文件，解压到./data目录下。

*[NOTE] 如果生成文本文件也可以，但读写速度和数据大小将翻倍，需要修改代码中的bfm_init函数的参数方可使用。*

*[NOTE] Release页面中bfm_visual_tool_with_data.exe自带数据，bfm_visual_tool_no_data.exe需要按上述步骤准备数据。*



## 功能介绍

### 生成随机人脸

设置`random range` 后的滑动条，可以调节随机程度（正态分布的方差），范围是0.0（平均脸）~2.0。

设置完成之后点击下方按钮即可在左侧生成随机人脸。

### 设置PC权重

可以修改面部Shape和Texture的PC权重，BFM共有199个PC可以在左侧下拉栏中选择，右测滑动条调节数值大小，范围是-10.0到+10.0，调节完成后点击对应的按钮完成设置。

*[NOTE] 修改PC权重需要在已经生成人脸的前提下使用*

### 将生成人脸存储到文件

目前支持的文件格式仅有PLY格式，可以通过MeshLab打开进行查看。



## 其他功能

### 预然人脸操作

该部分通过Qt5内置OpenGL实现，支持按键如下：

* 鼠标左键：长按后可以拖拉旋转人脸；
* 鼠标滚轮：缩放；
* 键盘A/W/S/D：向左转/放大/向右转/缩小。

