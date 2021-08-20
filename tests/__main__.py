import sys
import signal
import requests
import subprocess
import json
from time import sleep


CMD = [
    "valgrind",
    "-q",
    "--leak-check=full",
    "--show-leak-kinds=all",
    "--track-origins=yes",
    "-s",
    "./ft_stats",
]
EXIT_OK = 0
EXIT_ERR = 1
BASE_URL = "http://localhost:4242/api/v1"
TEST_VALID_USERS = [
    "vgoncalv",
    "iwillens",
    "hde-oliv",
    "rsiqueir",
    "gvitor-s",
    "nbarreir",
    "guiga",
    "mariah",
]
TEST_INVALID_USERS = [
    "vgoncal",
    "iwillenss",
    "hde_oliv",
    "rsiqueira",
    "",
]
LOG_FILE = "./tests/tests.log"


def log(res):
    with open(LOG_FILE, "a+") as f:
        f.write(res)


def _test(users, expected_status):
    """Run test for users list. Returns True if error."""
    e = False
    for user in users:
        r = requests.get(f"{BASE_URL}/{user}")
        log(
            "[{}] User: '{}' Status: {}\n".format(
                "OK" if r.status_code == expected_status else "KO",
                user,
                r.status_code,
            )
        )
        if r.status_code != expected_status:
            e = True
        if not r.ok:
            log("\n")
        else:
            log(json.dumps(r.json()) + "\n\n")
    return e


def tests():
    """Test the API endpoints. Returns exit code."""
    # Make valid requests
    if _test(TEST_VALID_USERS, 200):
        return EXIT_ERR
    # Make invalid requests
    if _test(TEST_INVALID_USERS, 404):
        return EXIT_ERR
    return EXIT_OK


if __name__ == "__main__":
    # Spawn the API server
    api = subprocess.Popen(CMD)
    # Wait for it to setup itself
    sleep(1)
    # Call tests
    exit_code = tests()
    # After tests are done, kills ft_stats
    api.send_signal(signal.SIGTERM)
    api.wait()
    # Exits with appropriate EXIT code
    sys.exit(exit_code)
