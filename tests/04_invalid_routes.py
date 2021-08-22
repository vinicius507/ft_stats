import pytest
import requests

BASE_URL = "http://localhost:4242"
INVALID_ROUTES = [
    "",
    "docs",
    "api",
    "api/v2",
    "api/v2",
    "api/vgoncalv",
    "vgoncalv",
    "hde-oliv",
    "42ft42ft42",
    "h",
]


@pytest.mark.parametrize("route", INVALID_ROUTES)
def test_get_invalid_routes(route):
    response = requests.get(f"{BASE_URL}/{route}")

    # Validate response status.
    assert response.status_code == 404
