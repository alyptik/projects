<xsl:stylesheet version="1.0"
    xmlns:atom="http://www.w3.org/2005/Atom"
    xmlns:content="http://purl.org/rss/1.0/modules/content/"
    xmlns:dc="http://purl.org/dc/elements/1.1/"
    xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    xmlns:rss="http://purl.org/rss/1.0/"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="text" omit-xml-declaration="yes"/>

    <xsl:template match="/atom:feed">
        <xsl:for-each select="atom:entry">
            <xsl:value-of select="atom:link/@href"/>
            <xsl:text>&#x9;</xsl:text>
            <xsl:value-of select="atom:title"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="/rdf:RDF">
        <xsl:for-each select="rss:item">
            <xsl:value-of select="rss:link"/>
            <xsl:text>&#x9;</xsl:text>
            <xsl:value-of select="rss:title"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="/rdf">
        <xsl:for-each select="rss:item">
            <xsl:value-of select="rss:link"/>
            <xsl:text>&#x9;</xsl:text>
            <xsl:value-of select="rss:title"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="/rss">
        <xsl:for-each select="channel/item">
            <xsl:choose>
                <xsl:when test="guid">
                    <xsl:value-of select="guid"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="link"/>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:text>&#x9;</xsl:text>
            <xsl:value-of select="title"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
