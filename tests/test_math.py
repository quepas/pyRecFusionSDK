import numpy as np
from numpy.testing import assert_equal

from pyRecFusionSDK import Mat3, Vec3, Vec3i


class TestVectors:
    def test_creation(self):
        v1 = Vec3(x=0.1, y=1.1, z=2.1)
        assert (v1.x, v1.y, v1.z) == (0.1, 1.1, 2.1)
        v2 = Vec3(0.1, 1.1, 2.1)
        assert (v2.x, v2.y, v2.z) == (0.1, 1.1, 2.1)
        v3 = Vec3i(x=3, y=2, z=1)
        assert (v3.x, v3.y, v3.z) == (3, 2, 1)
        v4 = Vec3i(3, 2, 1)
        assert (v4.x, v4.y, v4.z) == (3, 2, 1)

    def test_modification(self):
        v1 = Vec3(x=0.1, y=1.1, z=2.1)
        v1.y = 33.33
        assert (v1.x, v1.y, v1.z) == (0.1, 33.33, 2.1)
        v2 = Vec3i(x=3, y=2, z=1)
        v2.x, v2.z = 100, 200
        assert (v2.x, v2.y, v2.z) == (100, 2, 200)

    def test_repr(self):
        v1 = Vec3(x=0.1, y=1.1, z=2.1)
        assert repr(v1) == "Vec3(x=0.1, y=1.1, z=2.1)"
        v2 = Vec3i(x=3, y=2, z=1)
        assert repr(v2) == "Vec3i(x=3, y=2, z=1)"


class TestMat3:
    def test_creation(self):
        arr = [[1, 2, 3.3], [4, 5.5, 6], [7.7, 8, 9]]
        m1 = Mat3(arr)
        assert_equal(m1.data, arr)
        # Underlaying ndarray is always of type double (np.float64)
        assert m1.data.dtype == np.float64
        arr = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
        m2 = Mat3(np.array(arr))
        assert_equal(m2.data, arr)
        assert m2.data.dtype == np.float64

    def test_modification(self):
        arr = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
        m1 = Mat3(arr)
        # Apply some modifications; use different indexing schemes
        m1[1, 1] = 33
        m1[2][0] = 77
        m1.data[0, 0] = 89
        assert_equal(m1.data, [[89, 2, 3], [4, 33, 6], [77, 8, 9]])

    def test_matmul(self):
        m1 = Mat3([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        assert_equal((m1 @ m1).data, [[30, 36, 42], [66, 81, 96], [102, 126, 150]])

    def test_repr(self):
        m1 = Mat3([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        assert repr(m1) == "Mat3([[1, 2, 3], [4, 5, 6], [7, 8, 9]])"

class TestMat4:
    def test_matmul(self):
        pass
