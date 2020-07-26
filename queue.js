const mongoose = require('mongoose');

const Submission = require("./models/submission");
const User = require("./models/user");
const Problem = require("./models/problem");
const Registration = require('./models/registration');

const shell = require("shelljs");
const fs = require("fs");
const readline = require('readline');

let judging = false;

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

    let tests = 0, passed = 0, scr = 0;

    for await (const line of rl) {
        // Each line in input.txt will be successively available here as `line`.
        // console.log(`Line from file: ${line}`);
        
        tests++;
        
        if (line === "0") {
            passed++;
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
    } else {
        scr = (passed * 100) / tests;
    }

    let compilerMessage = fs.readFileSync('D:/SourceZ_Judge/CheckerEnv/Checker/compilation.txt', "utf8");

    console.log("TESTS: " + tests);
    console.log("PASSED: " + passed);
    console.log("SCORE: " + scr);

    Submission.findByIdAndUpdate(submId, { judged: true, compilerMessage: compilerMessage, results: res, verdict: verdict, score: scr}, (err, subm) => {
        if (err || !subm) {
            console.log(err);
            judging = false;
        } else {

            if(!subm.toContest || subm.toContest === "") {
                ///OLD ARCHIVE MODE SUBMISSION
                if (verdict === "Accepted") {
                    Problem.findOne({ name: subm.toProblem }, (err, pb) => {
                        pb.totalSubmissions += 1;
                        pb.acceptedSubmissions += 1;
                        pb.save();
                    });
                    User.findOne({ username: subm.author }, (err, user) => {
                        if (err || !user) {
                            ///nothing to worry
                            judging = false;
                        } else {
                            let solved = false;

                            for (let pb of user.solvedProblems) {
                                if (pb == subm.toProblem) {
                                    solved = true;
                                }
                            }

                            if (!solved) {
                                user.rating += 100;
                                user.solvedProblems.push(subm.toProblem);
                                user.save();
                            }

                            judging = false;
                        }
                    });
                } else {
                    Problem.findOne({ name: subm.toProblem }, (err, pb) => {
                        pb.totalSubmissions += 1;
                        pb.save();
                    });

                    judging = false;
                }
            } else {
                Registration.findOne({contestant: subm.author, contest: subm.toContest}, (err, reg) => {
                    if(err || !reg) {
                        judging = false;
                    } else {
                        console.log(subm.toProblem);
                        if(subm.pbInContest == 1) {
                            if(reg.p1_score < scr) {
                                reg.total_score += (scr - reg.p1_score);
                                reg.p1_score = scr;
                                reg.save();
                                judging = false;
                            } else {
                                judging = false;
                            }
                        } else {
                            if (reg.p2_score < scr) {
                                reg.total_score += (scr - reg.p2_score);
                                reg.p2_score = scr;
                                reg.save();
                                judging = false;
                            } else {
                                judging = false;
                            }
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

    if(judging === true) {
        console.log("Busy");
    } else {
        Submission.findOne({ judged: false }).sort({ created: 1 }).exec((err, sb) => {
            if (err || !sb) {
                console.log("No hit");
            } else {
                judging = true;
                Evaluate(sb);
            }
        });
    }
}, 3000);