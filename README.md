# Configuring Genetic Algorithm


This project provides the source code of the [submission](https://arxiv.org/pdf/2106.06304.pdf) __Automated Configuration of Genetic Algorithms by Tuning for Anytime Performance__.


Several packages are applied in this project:

* [__IOHexperimenter__](https://github.com/IOHprofiler/IOHexperimenter) provides the benchmark problems.
* [__Configurable GA__](https://github.com/FurongYe/ConfigurableGA) refers to the modular genetic algorithm to be configured.
* [__Irace__](https://github.com/cran/irace) implements an Iterated Race method for the automatic algorithm configuration.
* [__Bayesian Optimization Library__](https://github.com/wangronin/Bayesian-Optimization) implements the Bayesian Optimization (BO) algorithm working on decision spaces composed of either real, integer, categorical variables, or a mixture thereof. We use the `MIP-EGO` and `MIES` methods of the package.

Please contact [Furong Ye](mailto:f.ye@liacs.leidenuniv.nl) if you have questions about the project.