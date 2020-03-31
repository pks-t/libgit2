#include "clar_libgit2.h"
#include "branch.h"

static git_repository *repo;
static git_buf upstream_name;

void test_refs_branches_upstreamname__initialize_fs(void)
{
	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_buf_init(&upstream_name, 0));
}

void test_refs_branches_upstreamname__initialize_reftable(void)
{
	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo-reftable.git")));
	cl_git_pass(git_buf_init(&upstream_name, 0));
}

void test_refs_branches_upstreamname__cleanup(void)
{
	git_buf_dispose(&upstream_name);

	git_repository_free(repo);
	repo = NULL;
}

void test_refs_branches_upstreamname__can_retrieve_the_remote_tracking_reference_name_of_a_local_branch(void)
{
	cl_git_pass(git_branch_upstream_name(
		&upstream_name, repo, "refs/heads/master"));

	cl_assert_equal_s("refs/remotes/test/master", git_buf_cstr(&upstream_name));
}

void test_refs_branches_upstreamname__can_retrieve_the_local_upstream_reference_name_of_a_local_branch(void)
{
	cl_git_pass(git_branch_upstream_name(
		&upstream_name, repo, "refs/heads/track-local"));

	cl_assert_equal_s("refs/heads/master", git_buf_cstr(&upstream_name));
}
