# SourceZ_Judge

This is a NodeJs script that interacts with the MongoDB database behind SourceZ. It evaluates user's submissions in the following way:

* It checks the database every 3 seconds for a submission that is not judged
* If it gets a hit, it runs the checker (a bash script) that compiles and runs the user's code agains pre-constructed test data
* After the evaluation, it returns the verdict to the user (and, in case of a live contests, updates the rankings)

The bash script (evaluation script) can also be run locally. You just need to change the absolute path to the checkerEnv folder to match your machine.