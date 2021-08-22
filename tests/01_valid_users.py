import pytest
import requests
from jsonschema import validate

BASE_URL = "http://localhost:4242/api/v1"
RESPONSE_SCHEMA = {
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
        "intra_id": {"type": "integer"},
        "login": {"type": "string"},
        "name": {"type": "string"},
        "staff": {"type": "boolean"},
        "finished_projects": {"type": "integer"},
        "gpa": {"type": "number"},
        "stardew_coefficient": {"type": "number"},
    },
}
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


@pytest.mark.parametrize("intra_login", TEST_VALID_USERS)
def test_get_intra_users_validates_json_response_schema(intra_login):
    response = requests.get(f"{BASE_URL}/{intra_login}")

    # Validate response status.
    assert response.status_code == 200

    # Validate response content type header
    # assert response.headers["Content-Type"] == "application/json"

    # Validate will raise exception if given json is not what is described in
    # schema.
    body = response.json()
    validate(instance=body, schema=RESPONSE_SCHEMA)
