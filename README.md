# BFM模型可视化工具 - C++
通过C++和Qt5构建的一个Basel人脸模型（Basel Face Model, BFM）的可视化工具。

<img src="https://github.com/Great-Keith/bfm-visual-tool/raw/master/assets/avg_v1.1.png" width="80%">



## 数据准备

支持三种数据类型：二进制，文本，以及HDF5文件格式。

修改数据格式方式：

```c++
bfm_init();
// bfm_init(HDF5_DATA);
// bfm_init(BINARY_DATA);
// bfm_init(TEXT_DATA);
```

### HDF5格式（默认）

下载好BFM模型，将`model2009-publicmm1-bfm.h5`文件放置到`./data`文件夹中。

### 二进制格式

下载好BFM模型（2009年版本的`01_MorphableModel.mat`文件）后，通过`Matlab`脚本（提供于`./matlab_utils`目录下）将其转换成二进制文件用于读写。

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

*[NOTE] Release的v1.0版本使用的是二进制格式数据，其中bfm_visual_tool_with_data.exe自带数据，bfm_visual_tool_no_data.exe需要按上述步骤准备数据。*

### 文本格式

在`./matlab_utils` 中有脚本支持，但使用文本格式读写速度影响较大，不建议使用。



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

