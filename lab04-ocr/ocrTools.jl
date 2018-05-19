module OcrTools


"""
    makeDistk2(k)

Create a squared distance function using a specific kernel (scalar product)
function.

# Example:
```julia-repl
julia> eucDist = OcrTools.makeDistk2(OcrTools.linearKernel)
(::distk2) (generic function with 1 method)

julia> eucDist([3], [9])
36
```
"""
function makeDistk2(k)
    function distk2(v1::AbstractArray, v2::AbstractArray)
        k(v1, v1) + k(v2, v2) - 2 * k(v1, v2)
    end
end


"""
    linearKernel(v1, v2)

Euclidean scalar or dot product also called linear kernel.

# Example:
```julia-repl
julia> OcrTools.linearKernel([4, 5, 6], [1, 2, 3])
32
```
"""
function linearKernel(v1::AbstractArray, v2::AbstractArray)
    v1' * v2
end


"""
    makePolyKernel(a, b, c)

Create a polynomial scalar product function (polynomial kernel) using the given
a, b, c reals. The returned function implements the

```math
f(u, v) = (a \dot u' \dot v + b)^c
```

function.

# Example:
```julia-repl
julia> polyKernel = OcrTools.makePolyKernel(1, 0, 2)
(::polyKernel) (generic function with 1 method)

julia> polyKernel([5, 4], [1, 0])
25
```
"""
function makePolyKernel(a::Real, b::Real, c::Real)
    function polyKernel(v1::AbstractArray, v2::AbstractArray)
        (a * v1' * v2 + b)^c
    end
end


"""
    makeGaussKernel(sigma)

Creates a Gauss kernel function using the given sigma value.

# Example:
```julia-repl
julia> gaussKernel = OcrTools.makeGaussKernel(0.5)
(::gaussKernel) (generic function with 1 method)

julia> gaussKernel([2, -1, 0], [3, -4, -1])
2.7894680928689246e-10
```
"""
function makeGaussKernel(sigma::Real)
    sigmaSquared = sigma * sigma
    function gaussKernel(v1, v2)
        exp(-0.5 * norm(v1 - v2)^2 / sigmaSquared)
    end
end


"""
    dist2(v1, v2)

Calculates the square of the Eucledian distance between two points provided
as arrays.

# Example:
```julia-repl
julia> OcrTools.dist2([3, 5], [1, 2])
13
```
"""
dist2 = makeDistk2(linearKernel)


"""
    makeKNNCheck(kernel)

Create a function implementing the KNN algorithm
"""
function makeKNNCheck(kernel)
    dist2 = makeDistk2(kernel)

    function kNNCheck(k, trainingSet, testPoint)
        labelFreqs = Dict()
        dists = map(elem -> dist2(elem[1:end - 1], testPoint[1:end - 1]),
            trainingSet)
        for i = sortperm(dists)[1:k]
            label = trainingSet[i][end]
            labelFreqs[label] = get(labelFreqs, label, 0) + 1;
        end

        label = collect(keys(labelFreqs))[indmax(collect(values(labelFreqs)))]
        label, testPoint[end]
    end
end

end
