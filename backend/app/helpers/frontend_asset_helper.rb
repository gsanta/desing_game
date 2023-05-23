
module FrontendAssetHelper
  def javascript_pack_tag(entry)
    FrontendAsset.entry(entry).js.map { |js| "<script src=\"#{js}\"></script>" } .join.html_safe
  rescue NoMethodError => m
    raise "Invalid entry point #{entry}: #{m}"
  end
end
