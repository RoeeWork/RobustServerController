## hierarchy
---
The codebase is divided (conceptually) into three levels:
1. level 1 - main file
2. level 2 - **Command endpoints**, each represent a CLI command the project supports.  implemented in the codebase as `HandleCommand`.
3. level 3 - **Utility components** to be used by each other and the command endpoints.
   
![[Pasted image 20260706160244.png]]
#### Hierarchy rules
 - Each method in level 2 should only use methods/classes from level 3 and not from level 2 or level 1.
 - endpoint logic should be short and simple as a result of level 3's design, about 5-10 lines per method.
## Implementation workflow example
---
Lets look at an example as how a new command, say `$ rsc --removehost <HOSTNAME>` which removes a host `<HOSTNAME>` from the database could be implemented:

1. define user interaction, in our case `$ rsc --removehost <HOSTNAME>`.
2. Open the `HandleCommand` class (which we defined as the implementation of level 2 in our project), and add a new method `removeHostByName(std::string hostName)`.
3. define what is needed of our new method. in our case, we another method that finds `hostName` in the DB, another one that removes it and reports to the user.
4. json is handled in `JsonUtils`, so lets say we find a method that finds a `hostName` in the database, but doesnt remove it. at that point, we would want to implement it ourselves.
5. use the existing and new methods in our implementation of `removeHostByName` in `HandleCommand`.
6. CLI arguement parsing is handled in main, then we would need to call `HandleCommand::removeHostByName(hostName)`. 

This division allows for easier implementation of features, and makes contributions easier.

## Pushing to the repository
---
We'll define some rules for pushing new features/methods/fixes
- contributors should **ALWAYS** first make changes in **their own *local* branch** before pushing to the repository.
- To merge, push your local branch to the repository and open a PR (Pull Request) on github. after a review (assuming everything is in order) the changes will be pushed.

#### Example:
``` BASH
# update remote references
$ git:(REMOTE_BRANCH) git fetch origin

# create a new local working branch
$ git:(REMOTE_BRANCH) git switch -c <LOCAL_BRANCH> <REMOTE_BRANCH>
$ git:(LOCAL_BRANCH) ...

# work normally
$ git:(LOCAL_BRANCH) git add .
$ git:(LOCAL_BRANCH) git commit -m "stuff"
$ git:(LOCAL_BRANCH) ...

# push local branch to remote
$ git:(LOCAL_BRANCH) git push -u origin <LOCAL_BRANCH>

# after pusing, create a new PR on github.

# in case the remote branch was updated,
# fetch updates and rebase.
$ git:(LOCAL_BRANCH) git fetch origin
$ git:(LOCAL_BRANCH) git rebase <REMOTE_BRANCH>

# resolve conflicts if needed
$ git:(LOCAL_BRANCH) git add <resolved-files>
$ git:(LOCAL_BRANCH) git rebase --continue

# update PR
$ git:(LOCAL_BRANCH) git push --force-with-lease

```