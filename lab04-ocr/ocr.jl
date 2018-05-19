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
        # write(f, "(calculated, expected)\n")
        badCounts = zeros(10)
        allCounts = zeros(10)

        counter = function (result)
            allCounts[result[2] + 1] += 1
            if (result[1] != result[2])
                badCounts[result[1] + 1] += 1
            end
            # write(f, "$(result[1]), $(result[2])\n")
        end

        map(counter, solveKNN(ARGS...))
        for i = 1:10
            write(f, "Error percentage for number ",
                "$(i - 1): $(badCounts[i] / allCounts[i] * 100)%\n")
        end
        # write(f, "$(badCount / allCount * 100)% error\n")
    end
else
    println("Please provide the filenames of the training dataset and the ",
        "test dataset!")
end
