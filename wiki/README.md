
# Table of Contents

1.  [Scatter](#orgad737b4)
    1.  [Theory](#org2f1ae15)
    2.  [Algorithms](#orgf672793)
    3.  [Data](#orga85b2b9)
    4.  [Notes](#org9753e75)



<a id="orgad737b4"></a>

# Scatter


<a id="org2f1ae15"></a>

## Theory


### Introduction

The scatter pattern is another parallel access pattern and the inverse of the gather pattern.
One is given a set of input data and a set of indices defining where the input data is to written.
The scatter operation is completely defined by `output[idx[i]] = input[i]`.
However, unlike gather, scatter is ill-defined when duplicate write addresses appear, see Fig. [2](#orga72461a).

<figures/undef.pdf>

It is unclear how such collisions should be resolved without any rules.
There are four simple solutions being presented in [Variants](#orgefe8082).

The simplest serial version of scatter is shown in [1](#org19f23cb).

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


<a id="orgefe8082"></a>

### Variants

1.  Permutation

    <figures/permutation.pdf>

2.  Atomic

    <figures/atomic.pdf>

3.  Merge

    <figures/merge.pdf>

4.  Priority

    <figures/priority.pdf>


### Expectations

The first impression data should come into mind looking at [1](#org19f23cb), is that there are no dependencies in the loop.
Meaning that this operation is highly parallizeable.


<a id="orgf672793"></a>

## Algorithms


<a id="orga85b2b9"></a>

## Data


<a id="org9753e75"></a>

## Notes

