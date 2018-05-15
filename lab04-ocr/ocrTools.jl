module OcrTools

"""
    dist(v1, v2)

Calculates the Eucledian distance between two points provided as arrays.

# Example:
```julia-repl
julia> dist([3, 5], [1, 5])
4.47213595499958
```
"""
function dist(v1::AbstractArray, v2::AbstractArray)
    sqrt(foldr(+, (v1 - v2).^2))
end

function kernelDist(k, v1, v2)
    dv = v1 - v2
    k(dv, dv)
end

function linearKernel(v1::AbstractArray, v2::AbstractArray)
    v1' * v2
end

function makePolyKernel(a::Real, b::Real, c::Real)
    function polyKernel(v1::AbstractArray, v2::AbstractArray)
        (a * v1' * v2 + b)^c
    end
end

function makeGaussKernel(sigma::Real)
    sigmaSquared = sigma * sigma
    function gaussKernel(v1, v2)
        exp(0.5 * norm(v1 - v2)^2 / sigmaSquared)
    end
end


function makeKNNCheck(kernel)
    function kNNCheck(k, trainingSet, testPoint)
        labelFreqs = Dict()
        dists = map(elem -> dist(elem[1:end - 1], testPoint[1:end - 1]),
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
