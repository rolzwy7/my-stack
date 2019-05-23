from config import LST_IND, FILE_IND


class OptionExt():

    def __init__():
        pass

    # def _validate_ext(self, value):
    #     # List conversion - exceptions
    #     if self.opt_is_list is False:
    #         raise Exception(
    #             "Can't convert '%s' to list, opt_is_list=%s" % (
    #                 self.opt_name, self.opt_is_list
    #             ))
    #     if self.opt_is_list is False:
    #         raise Exception(
    #             "Argument '%s' needs to be passed with list indicator '%s'" % (
    #                 self.opt_name, LST_IND
    #             ))

    def _parse_list_from_cmd_line(self, value):
        temp = value
        ret = []
        temp = temp[len(LST_IND):].strip("[").strip("]").strip(",")
        temp = temp.split(",")
        for _ in temp:
            elem = self.opt_type(_.strip(" ").strip(""))
            ret.append(elem)
        ret = list(set(ret))
        ret = sorted(ret)
        return ret

    def _parse_list_from_file(self, value):
        filepath = value[len(FILE_IND):].strip(" ").strip('"')
        ret = []
        with open(filepath, "rb") as source:
            for line in source:
                if line != b"":
                    ret.append(line.strip(b"\n").strip(b"\r\n"))
            source.close()
        ret = map(lambda x: str(x, "utf8"), ret)
        ret = list(set(ret))
        ret = sorted(ret)
        return ret

    def set_option_value_extended(self, value):
        # List/cmd
        if value.startswith(LST_IND) and self.opt_is_list is True:
            try:
                return self._parse_list_from_cmd_line(value)
            except Exception as e:
                raise

        # List/file (line by line)
        if value.startswith(FILE_IND) and self.opt_is_list is True:
            try:
                return self._parse_list_from_file(value)
            except Exception as e:
                raise

        # Int, String
        if self.opt_type in [int, str]:
            return self.opt_type(value.strip(" ").strip(""))

        # Bool
        if self.opt_type in [bool]:
            v = value.strip(" ").strip("")
            ret = True if v in (True, "true", "True", "1") else None
            if ret is not None:
                return ret
            ret = False if v in (False, "false", "False", "0") else None
            if ret is not None:
                return ret
            raise Exception(
                "Valid values for '%s': [true, false]" % self.opt_name
            )
