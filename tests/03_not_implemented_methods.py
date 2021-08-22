import pytest
import requests

BASE_URL = "http://localhost:4242/api/v1"
VALID_ROUTES = ["", "vgoncalv"]


@pytest.mark.parametrize("route", VALID_ROUTES)
def test_post_invalid_methods_valid_routes(route):
    response = requests.post(f"{BASE_URL}/{route}")

    # Validate response status.
    assert response.status_code == 405


@pytest.mark.parametrize("route", VALID_ROUTES)
def test_put_invalid_methods_valid_routes(route):
    response = requests.put(f"{BASE_URL}/{route}")

    # Validate response status.
    assert response.status_code == 405


@pytest.mark.parametrize("route", VALID_ROUTES)
def test_patch_invalid_methods_valid_routes(route):
    response = requests.patch(f"{BASE_URL}/{route}")

    # Validate response status.
    assert response.status_code == 405


@pytest.mark.parametrize("route", VALID_ROUTES)
def test_delete_invalid_methods_valid_routes(route):
    response = requests.delete(f"{BASE_URL}/{route}")

    # Validate response status.
    assert response.status_code == 405
