from pyRecFusionSDK import build_version, major_version, minor_version, token, version


class TestRecFusionSDK:
    def test_version(self):
        # NOTE: actually, there is no other SDK version that we could use!
        #       This needs to be updated if a new version is released.
        assert major_version() == 2
        assert minor_version() == 2
        assert build_version() == 0
        assert version() == "2.2.0"

    def test_machine_token(self):
        machine_token = token()
        assert len(machine_token) == 32
        # TODO: this could be more strict! Especially, isalpha()
        assert all(map(lambda x: x.isdigit() or x.isalpha(), machine_token))
