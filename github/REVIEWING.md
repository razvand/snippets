# Git / GitHub  Reviewing Workflow

Reviewing is done via the GitHub pull request interface, generally following the [GitHub guidelines](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests).

Reviewing implies 5 actions:

1. Reviewing the commit messages and metadata (signature, authorship)

1. Reviewing the content of the contribution: good design, implementation value, readability, compliance

1. Testing changes, making sure the fix the problem or they add the proposed feature, making sure they don't break anything

1. Submitting the review

1. Discussing and iterating

All of these actions can rely on automation, such as linters, static analysis tools, unit testing / integration testing, typically included in CI/CD pipelines, such as those provided by [GitHub Actions](https://docs.github.com/en/actions).

## Set Up

Doing the review requires two items:

1. Be logged in on GitHub and have reviewer access to the pull request.
   The second part means that you have access to the pull request (in case of a private) repository.

   In order to be formally assigned as a reviewer to a pull request in the GitHub interface, you have to have the [`Triage` role the repository](https://docs.github.com/en/organizations/managing-user-access-to-your-organizations-repositories/managing-repository-roles/repository-roles-for-an-organization).
   This role is assigned to you by a admin member of the repository.
   This role is not a requirement, you can do a review without being assigned as a reviewer.

1. Have a local clone of the repository (or a clone of your fork of the repository).
   So you either did, at point, `git clone <URL>` using the `<URL>` of the main repository, or using the `<URL`> of your [fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/about-forks) of that repository.

For the first item, you browser should have opened the GitHub pull request.

For the second item, you will configure your local repository to point to the branch used to create the pull request.
For this, do the following:

1. Be sure you are located, using the command line, on the local copy of the repository.

1. Copy the link mentioned in the `from <username>:<branch>` part of the pull request.
   This is the link to the contribution source.
   E.g. `https://github.com/cluosh/unikraft/tree/staging`, `https://github.com/michpappas/unikraft/tree/michpappas/feature/libukmemtag`.

   The link stores 3 important pieces of information of the remote contribution:

   1. The username: `cluosh` and `michpappas`
   1. The repository name: `unikraft` and `unikraft`
   1. The branch name: `staging` and `michpappas/feature/libukmemtag`

   Copy paste the link and edit it to only include the username and the repository name.
   Remove the branch part, that is anything in the URL starting from and including `/tree/...`.
   E.g. `https://github.com/cluosh/unikraft`, `https://github.com/michpappas/unikraft`.

1. **Note**: This step is required if this is the first time you add a given remote.
   If you have added a remote for the username before, you ca skip this step.
   You can try the command below and, if you get a message such as `remote ... already exists`, you can go to the next step.

   ```console
   git remote add <username> <URL>
   ```

   where `<username>` is the username in the URL, e.g. `cluosh`, `michpappas`.
   E.g.:

   ```console
   git remote add cluosh http://github.com/cluosh/unikraft
   git remote add michpappas https://github.com/michpappas/unikraft
   ```

   Verify it was added correctly by using:

   ```console
   git remote show <username>
   ```

   E.g.:

   ```console
   git remote show cluosh
   git remote show michpappas
   ```

1. Check the remote branch that was used to create the pull request:

   ```console
   git branch -a
   ```

   In the output of the above command you should see a line `remotes/<username>/<branch>`.
   If you don't see that, you did something wrong and you need to remove and recreate the remote, via the `git remote` command.

1. Fetch the contribution from the remote end:

   ```console
   git fetch <username>
   ```

   E.g.:

   ```console
   git fetch cluosh
   git fetch michpappas
   ```

1. Create a local branch of the contribution:

   ```console
   git checkout -b <local-branch-name> <username>/<branch>
   ```

   where:

   - `<username>` is the name of the remote
   - `<branch>` is the name of the remote branch
   - `<local-branch-name>` is the name of the local branch you will use

   The name of the local branch is something you choose.
   Generally, it is advised to keep the same name as `<branch>`.
   However, it may be the case that the contributor uses a value for `<branch>` that conflicts with an existing local one (such as `main` or `master` or `testing`).
   In that case, it is suggested to use `<username>-<branch>` for the local branch name.

   E.g.:

   ```console
   git checkout -b cluosh-staging cluosh/staging
   git checkout -b michpappas/feature/libukmemtag michpappas/michpappas/feature/libukmemtag
   ```

   In case of the first command, we used `<username>-<branch>` for the local branch.
   This is because the remote branch name (`staging`) conflicted with a local branch name called the same (`staging`).

   In the case of the second command we used the same name for the local branch as for the remote branch: `michpappas/feature/libukmemtag`.
   Note that there is a recommendation to use, as branch name, the format `<username>/<branch-detail>`, to be able to pin the branch name to the user creating it.

So, at this point you should have:

- Your browser pointing out to the pull request interface on GitHub.
- Your local repository pointing to the contents of the remote branch used in the pull request.

We will detail the 5 review action below, mentioning whether they will happen either on the GitHub pull request interface or locally, on the clone of the repository.

## Review Commit Metadata

Reviewing the commit metadata happens locally.
Use the command to browse through the metadata of commits:

```console
git log
```

Check the commits in the contributions and make sure they follow [good commit practices](https://cbea.ms/git-commit/).
Generally, this means:

1. The first line of the commit message (the title) is a representative line, that's not very long (ideally, but not strictly, limited at 50 characters).
   The title line typically has a prefix that points to the type of contribution and/or the location in the repository.
   This is generally stated as part of the repository contributor conventions.

1. Make sure there is an empty line after the title line and the rest of the commit message (the body).

1. Make sure the lines in the body are limited to 72 characters.

1. Make sure there are no typos or spelling mistakes in the title or body.

1. Make sure the author is properly stated, generally in the form of `Firstname Lastname <email>`.

1. If the commit conventions use or imply using a [`Signed-off-by` line](https://stackoverflow.com/a/14044024/4804196), make sure that line also has the author properly stated.
   Also make sure the exact same name are used for both the author and the `Signed-off-by` line.

1. Make sure the commit message is readable and to the point.
   Make sure it clearly details what the commit does.
   Make sure it fits the content of the commit (the actual contribution);
   i.e. when you check the changes in the commit, they are well connected to the message;
   that is they don't mention more or less than the commit contents.

You will submit any issues in the general review message.

## Review Contents

Reviewing contents is done both in the pull request GitHub interface and locally.

In the pull request GitHub interface, go the to the `Files changed` tab where you can see an interactive view of the changes.
Walk through the changes and check for anything that may not be good / correct:

- hard to read content
- typos
- violation of general coding / writing conventions
  - lines to large
  - missing newlines at the end of the files
  - training white spaces
  - improper indentation
- violation of project coding / writing conventions
- general coding / writing mistakes
- project-specific coding / writing mistakes

Follow the [GitHub review guidelines](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests/reviewing-proposed-changes-in-a-pull-request) and add your request for changes.
In the GitHub interactive interface in the `Files changed` tab you can request changes either on a single line or on multiple lines, where the `+` icon appears when hovering.
You can request changes as feedback text or as concrete content update suggestions, as shown in the [GitHub review guidelines](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/reviewing-changes-in-pull-requests/reviewing-proposed-changes-in-a-pull-request) and add your request for changes.

Locally you can get a unified view of the changes inside files.
You can open a file and check out its entirety: existing content and newly contributed content.
You can check the newly contributed content and make sure that:

- It is consistent with existing content: same structure, same format, same conventions.
- It is readable and integrates well with existing content.

Finally, you want to be sure that the content is well aligned with the commits it is part of.
Each commit should do one thing and do one thing well, and the content and commit should be aligned.

For that, go through each commit in the contribution, from the oldest to the most recent one.
Find the commit IDs by using:

```console
git log
```

Go to the history and get the oldest commit ID (the commit hash) and then check it.
Then get the next commit ID and check it.
And so on.

To check each commit use:

```console
git show <commit_id>
```

where `<commit_id>` is the ID (hash) of the commit.

When checking the commit be sure that:

- The commit message and the commit contents correspond.
  The commit message should not state anything more or less than the contents.

- The commit is "atomic".
  That is, it does one thing and one thing well.

  You may have two situations:

  1. The commit is too "large", it has multiple contributions.
     In this case, the feedback should be to split to commit in smaller "atomic" commits, each per contribution.

  1. The commit is too small.
     There are multiple commits related to the same contribution.
     In this case, the feedback should be to squash the commits into a single commit.

In case of issues with individual commits, you will reference them by ID (or link) in the general review message.
You can get a link to the commit in the `Commits` tab in the pull request interface on GitHub.

## Test Changes

In the above steps, you checked the contribution without actually using it.
Changes must be tested to make sure they are correct and don't break anything.

Ideally, the repository has CI/CD pipelines configured that automate testing of common items.
This generally relies on the repository itself featuring tests that can be called automatically.

Even if this is the case, there may be specific tests that you want do manually.

When reviewing documentation contributions, make sure you run the documented actions (commands or otherwise) to ensure they work OK.

Testing is generally particular to the repository.
Do your best in ensuring that contributions work as expectedly and they don't introduce additional bugs.

You will submit any issues resulting from the testing phase in the general review message.

## Submit Review

You submit the review in the pull request interface on GitHub.

In the `Files changed` tab, click on the `Review changes` button and add your review in the pop-up text area.
This is a step that you will do from the beginning, and keep adding contents to the review message as you go through the review changes.
Note that if you click outside of the pop-up text are, it will close, but the review message is still there;
you can get back to it by clicking the `Review changes` button again.
This is useful because reviewing is an ongoing process and you may want to switch between filling the pop-up text area, adding suggestions, or checking the commits in the `Commits` tab.

Once the text and suggestions of your review are complete, in the pop-up text area check on of the three buttons: `Comment`, `Approve` or `Request changes`.
Typically, you choose `Approve` in case all is OK with the pull request and it can be merged, from your point of view;
and you choose `Request changes` in case changes are required, as you detail in the suggestions and in the review text.

Finally, click the `Submit review` button and complete the review.

## Discussion and Iteration

After the review is submitted, the pull request author will address the issues.
The author will update the commit messages and contents.
And will also start conversations on the main tab (`Conversation`) on the pull request on GitHub.

As a reviewer, you will add your input to conversations to clarify the review or reach an agreement regarding part of the contribution.

With conversations settled and the commit contents updated, you will be asked to do another review round.
For the new round, you will iterate through the same steps above and then resubmit a new review.

The steps above are the same, expect for getting the contribution updates.
To get the updates, make sure you are on the local branch:

```console
git status
```

If not, checkout to the local branch:

```console
git checkout <local-branch-name>
```

E.g.:

```console
git checkout cluosh-staging
```

or:

```console
git checkout michpappas/feature/libukmemtag
```

And update the branch with the updated contents of the contribution:

```console
git fetch <username>
git reset --hard <username>/<branch-name>
```

E.g.:

```console
git fetch cluosh
git reset --hard cluosh/staging
```

or:

```console
git fetch michpappas
git reset --hard michpappas/michpappas/feature/libukmemtag
```

With a new review submitted, the author will address comments and you will iterate.

For larger projects, it's common to have multiple review rounds.
This, of course depends, on the contribution complexity.
