include("./ocrTools.jl")

using OcrTools
using CSV
using DataFrames


function readTrainingSet(trainingName)
    dataset = CSV.read(trainingName, delim=",", datarow=1)
    trainingSet = Array{Int16,1}[]
    for i = 1:size(dataset)[1]
        row = convert(Array{Int16}, dataset[i, :])[1, :]
        push!(trainingSet, row)
    end
    trainingSet
end

function readTestSet(testName)
    CSV.read(testName, delim=",", datarow=1)
end


function solveKNN(kernel, trainingName, testName)
    kNNCheck = OcrTools.makeKNNCheck(kernel)
    trainingSet = readTrainingSet(trainingName)

    testSet = readTestSet(testName)

    calclatedAndExpected = []

    for i = 1:size(testSet)[1]
        row = convert(Array{Int16}, testSet[i, :])[1, :]
        push!(calclatedAndExpected, kNNCheck(15, trainingSet, row))
    end

    calclatedAndExpected
end



function main(args)
    if length(args) != 4
        println("Please provide the filenames of the training dataset and the ",
            "test dataset!")
    else
        if (args[2] == "1")
            kernel = OcrTools.linearKernel
            println("Using linear kernel...")
        elseif (args[2] == "2")
            kernel = OcrTools.makePolyKernel(3, -1, 2)
            println("Using polynomial kernel...")
        else
            kernel = OcrTools.makeGaussKernel(100)
            println("Using Gauss kernel...")
        end

        badCounts = zeros(10)
        allCounts = zeros(10)

        function counter(result)
            calculated, expected = result
            allCounts[expected + 1] += 1
            if (calculated != expected)
                badCounts[expected + 1] += 1
            end
        end

        map(counter, solveKNN(kernel, args[3], args[4]))
        for i = 1:10
            println("Error percentage for number ",
                "$(i - 1): $(badCounts[i] / allCounts[i] * 100)%")
        end
    end
end


main(ARGS)
