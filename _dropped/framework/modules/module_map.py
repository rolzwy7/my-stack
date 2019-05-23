from framework.modules.development.development_module import Module as development_module
from framework.modules.exploits.cameras.netwave.kcore_dump import Module as kcore_dump

from config import DEV_MODE


class ModuleMap():
    def __init__(self):
        # Link new modules
        self._arr = [
            {
                "handle": kcore_dump,
                "use_name": "kcore_dump"
            },
        ]
        if DEV_MODE:
            self._arr.append({
                "handle": development_module,
                "use_name": "development_module"
            })
        self.parse_modules()

    def parse_modules(self):
        _temp_arr = []
        for it, val in enumerate(self._arr):
            tmp = {"id": it + 1}
            tmp = {**tmp, **val}
            _temp_arr.append(tmp)
        self._arr = _temp_arr

    def by_id(self, mid):
        for _ in self._arr:
            if _["id"] == mid:
                return _
        return None

    def by_name(self, mname):
        for _ in self._arr:
            if _["use_name"] == mname:
                return _
        return None
