package flash.errors {
    public interface IParserState {
        function get lineNumber():uint;
        function get lineOffset():uint;
        function get index():uint;
    }
}
