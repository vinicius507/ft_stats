import pytest
import requests

BASE_URL = "http://localhost:4242/api/v1"
TEST_INVALID_USERS = [
    "vgoncal",
    "iwillenss",
    "hde_oliv",
    "rsiqueira",
    "",
]


@pytest.mark.parametrize("intra_login", TEST_INVALID_USERS)
def test_get_intra_invalid_users_check_status_code_404(intra_login):
    response = requests.get(f"{BASE_URL}/{intra_login}")

    # Validate response status.
    assert response.status_code == 404
