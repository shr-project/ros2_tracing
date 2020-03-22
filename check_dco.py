# Copyright 2020 Christophe Bedard
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Check that all commits for the proposed change are signed off."""

import os
import sys


# See: https://docs.gitlab.com/ee/ci/variables/predefined_variables.html
ENV_COMMIT_SHA = 'CI_COMMIT_SHA'
ENV_COMMIT_SHA_BEFORE = 'CI_COMMIT_BEFORE_SHA'


def main() -> int:
    commit_sha = os.environ.get(ENV_COMMIT_SHA, None)
    if commit_sha is None:
        print(f'could not get environment variable: \'{ENV_COMMIT_SHA}\'')
        return 1
    commit_sha_before = os.environ.get(ENV_COMMIT_SHA_BEFORE, None)
    if commit_sha_before is None:
        print(f'could not get environment variable: \'{ENV_COMMIT_SHA_BEFORE}\'')
        return 1

    return 0


if __name__ == '__main__':
    sys.exit(main())
