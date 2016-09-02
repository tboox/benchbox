# The Benchmark Testing Box

## Introduction

Benchbox is a benchmark testing utilities.

## Build

Please install xmake first: [xmake](http://xmake.io)

```bash
    $ xmake
```

## Run case

```bash
    $ xmake coroutine -n switch
or  $ xmake coroutine --casename switch
```

## List tests

```bash
    $ xmake --help
```

The results:

```
    ...

Tasks: 
       coroutine         The coroutine benchmark.
       other             The other benchmark.
```

## List cases

```bash
    $ xmake coroutine --help
```

The results:

```
The coroutine benchmark.

Options: 

    ...

    -n CASENAME, --casename=CASENAME       The case name.
                                               - switch
```

#### Contacts

* Email：[waruqi@gmail.com](mailto:waruqi@gmail.com)
* Homepage：[TBOOX Open Source Project](http://www.tboox.org/cn)
* Community：[TBOOX Open Source Community](http://www.tboox.org/forum)

## 简介

Benchbox是一个基准测试包，里面包含许多针对第三方库功能的性能基准测试和对比。

例如：各大开源协程库性能基准测试，等等

## 编译

请先安装: [xmake](http://xmake.io)

然后运行：

```bash
    $ xmake
```

## 运行测试case

```bash
    $ xmake coroutine -n switch
or  $ xmake coroutine --casename switch
```

## 显示所有测试用例

```bash
    $ xmake --help
```

结果如下：

```
    ...

Tasks: 
       coroutine         The coroutine benchmark.
       other             The other benchmark.
```

## 显示某个测试的所有case

```bash
    $ xmake coroutine --help
```

结果如下:

```
The coroutine benchmark.

Options: 

    ...

    -n CASENAME, --casename=CASENAME       The case name.
                                               - switch
```

#### 联系方式

* 邮箱：[waruqi@gmail.com](mailto:waruqi@gmail.com)
* 主页：[TBOOX开源工程](http://www.tboox.org/cn)
* 社区：[TBOOX开源社区](http://www.tboox.org/forum)
* QQ群：343118190
* 微信公众号：tboox-os

