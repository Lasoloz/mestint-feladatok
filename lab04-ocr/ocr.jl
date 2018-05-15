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


function solveKNN(trainingName, testName)
    kNNCheck = OcrTools.makeKNNCheck(OcrTools.linearKernel)
    trainingSet = readTrainingSet(trainingName)

    testSet = readTestSet(testName)

    calclatedAndExpected = []

    for i = 1:size(testSet)[1]
        row = convert(Array{Int16}, testSet[i, :])[1, :]
        push!(calclatedAndExpected, kNNCheck(15, trainingSet, row))
    end

    calclatedAndExpected
end



if length(ARGS) == 2
    open("results", "w") do f
        write(f, "(calculated, expected)\n")
        badCount = 0
        allCount = 0

        writer = function (result)
            allCount += 1
            if (result[1] != result[2])
                badCount += 1
            end
            write(f, "$(result[1]), $(result[2])\n")
        end

        map(writer, solveKNN(ARGS...))
        write(f, "$(badCount / allCount * 100)% error\n")
    end
else
    println("Please provide the filenames of the training dataset and the ",
        "test dataset!")
end
