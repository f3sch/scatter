
# Table of Contents

1.  [Scatter](#orgb492d7f)
    1.  [Theory](#org29c36e5)
    2.  [Algorithms](#org23efaa8)
    3.  [Data](#orgf2aef69)
    4.  [Notes](#orgac23be5)



<a id="orgb492d7f"></a>

# Scatter


<a id="org29c36e5"></a>

## Theory


### Introduction

The scatter pattern is another parallel access pattern and the inverse of the gather pattern.
One is given a set of input data and a set of indices defining where the input data is to written.
The scatter operation is completely defined by `output[idx[i]] = input[i]`.
However, unlike gather, scatter is ill-defined when duplicate write addresses appear, see Fig. [2](#org67d210a).

![img](figures/undef.png "Undefined scatter")

It is unclear how such collisions should be resolved without any rules.
There are four simple solutions being presented in [1.1.2](#orgfc6eded).

The simplest serial version of scatter is shown in [1](#orgd2a6fb1).

    template <typename Data = double, typename Idx = size_t>
    void scatter(vector<Data> &input, vector<Idx> &idx, vector<Data> &output)
    {
      auto N = idx.size(); // get index size
      for (auto i = 0; i < N; ++i) {
        auto j = idx[i]; // get ith index;
        assert(0 <= j && j < N); //check bounds
        output[j] = input[i]; // perform random write
      }
    }


<a id="orgfc6eded"></a>

### Variants

1.  Permutation

    ![img](figures/permutation.png "Permutation scatter")

2.  Atomic

    ![img](figures/atomic.png "Atomic scatter")

3.  Merge

    ![img](figures/merge.png "Merge scatter")

4.  Priority

    ![img](figures/priority.png "Priority scatter")


### Expectations

The first impression data should come into mind looking at [1](#orgd2a6fb1), is that there are no dependencies in the loop.
Meaning that this operation is highly parallizeable.


<a id="org23efaa8"></a>

## Algorithms


<a id="orgf2aef69"></a>

## Data


<a id="orgac23be5"></a>

## Notes

