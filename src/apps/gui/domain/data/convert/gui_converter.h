#pragma once

#include <base/model/ItemType.h>


struct GuiTag {};

DEF_CONVERT(GuiTag, std::string, ItemInt)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemUInt)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemLong)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemULong)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemLongLong)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemFloat)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemDouble)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemLongDouble)
return std::to_string(in.val);
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemString)
return in.val;
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemBytes)
return std::to_string(in.val).append(" Bytes");  // todo
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemTimeStamp)
return std::to_string(in.val).append(" Seconds From 1970/01/01");  // todo
END_DEF

DEF_CONVERT(GuiTag, std::string, ItemDuration)
return std::to_string(in.val).append(" Seconds");  // todo
END_DEF

DEF_CONVERT_DYNAMIC(GuiTag, std::string)
