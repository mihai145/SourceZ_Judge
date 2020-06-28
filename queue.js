const mongoose = require('mongoose');

const Submission = require("./models/submission");
const User = require("./models/user");
const Problem = require("./models/problem");

const shell = require("shelljs");
const fs = require("fs");
const readline = require('readline');

///-----------------------///
///DATABASE SETUP
///-----------------------///
mongoose.connect(process.env.DB_URI, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
    useFindAndModify: false
});

async function processLineByLine(submId) {
    const fileStream = fs.createReadStream("D:/SourceZ_Judge/CheckerEnv/Checker/results.txt");

    const rl = readline.createInterface({
        input: fileStream,
        crlfDelay: Infinity
    });
    // Note: we use the crlfDelay option to recognize all instances of CR LF
    // ('\r\n') in input.txt as a single line break.

    let res = [];
    let verdict = "Accepted";

    for await (const line of rl) {
        // Each line in input.txt will be successively available here as `line`.
        // console.log(`Line from file: ${line}`);

        if (line === "0") {
            res.push("Correct");
        } else if (line === "1") {
            res.push("Wrong answer");
            if (verdict === "Accepted") {
                verdict = "Wrong Answer";
            }
        } else if (line === "2") {
            res.push("Time limit exceeded");
            if (verdict === "Accepted") {
                verdict = "Time limit exceeded";
            }
        } else {
            res.push("Runtime error");
            if (verdict === "Accepted") {
                verdict = "Runtime Error";
            }
        }
    }

    if (res.length === 0) {
        verdict = "Compilation Error";
    }

    let compilerMessage = fs.readFileSync('D:/SourceZ_Judge/CheckerEnv/Checker/compilation.txt', "utf8");

    Submission.findByIdAndUpdate(submId, { judged: true, compilerMessage: compilerMessage, results: res, verdict: verdict }, (err, subm) => {
        if (err || !subm) {
            console.log(err);
        } else {

            if (verdict === "Accepted") {
                User.findOne({ username: subm.author }, (err, user) => {
                    if (err || !user) {
                        ///nothing to worry really
                    } else {
                        let alreadySolved = false;

                        for (const pb of user.solvedProblems)
                            if (pb === subm.toProblem) {
                                alreadySolved = true;
                                break;
                            }

                        if (!alreadySolved) {
                            user.solvedProblems.push(subm.toProblem);
                            user.rating = user.rating + 100;
                            user.save();

                            Problem.findOne({ name: subm.toProblem }, (err, prob) => {
                                if (err || !prob) {
                                    ///nothing to worry really
                                } else {
                                    prob.solvedBy = prob.solvedBy + 1;
                                    prob.save();
                                }
                            });
                        }
                    }
                });
            }
        }
    });
}

function Evaluate(subm) {
    const author = subm.author;
    const pb = subm.toProblem;
    
    console.log("HIT " + author + " " + pb);

    const cpp = subm.cpp;
    fs.writeFileSync("D:/SourceZ_Judge/CheckerEnv/Checker/current.txt", cpp, "utf8");
    
    const commandString = "sh D:/SourceZ_Judge/CheckerEnv/Checker/check.sh " + pb;

    shell.exec(commandString);

    processLineByLine(subm._id);
}

setInterval(() => {
    console.log("Started interval");
    Submission.findOne({ judged: false }).sort({ created: 1 }).exec((err, sb) => {
        if (err || !sb) {
            console.log("No hit");
        } else {
            Evaluate(sb);
        }
    });
}, 5000);